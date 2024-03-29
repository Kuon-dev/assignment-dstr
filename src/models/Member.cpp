#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

#include "../modules/InputHandler.cpp"

using namespace std;

struct userNode {
	userNode* PrevAddress;
	userNode* NextAddress;
	string UserId;
	string userUserName;
	string UserPassword;
	string UserName;
	int UserAge;
	string UserGender;
	string UserEmail;
	string UserContact;
	string UserLastLogin;
};

class userList {
	userNode* head = nullptr;
	userNode* tail = nullptr;

	public:
	userNode* getHead() { return head; }
	userNode* getTail() { return this->tail; }

	void addUserNode(userNode* newUserNode) {
		if (head == nullptr) {
			head = tail = newUserNode;
		} else {
			tail->NextAddress = newUserNode;
			newUserNode->PrevAddress = tail;
			tail = newUserNode;
		};
	}

	void readSpecificUserNode(string userId) {
		userNode* currentNode = head;
		while (currentNode != nullptr && currentNode->UserId != userId) {
			currentNode = currentNode->NextAddress;
		}
		if (currentNode == nullptr) {
			cout << "User with ID " << userId << " not found." << endl;
		} else {
			cout << "User Details:" << endl;
			cout << "User ID: " << currentNode->UserId << endl;
			cout << "Username: " << currentNode->userUserName << endl;
			cout << "Name: " << currentNode->UserName << endl;
			cout << "Age: " << currentNode->UserAge << endl;
			cout << "Gender: " << currentNode->UserGender << endl;
			cout << "Email: " << currentNode->UserEmail << endl;
			cout << "Contact: " << currentNode->UserContact << endl;
			cout << "Last Login: " << currentNode->UserLastLogin << endl;
		}
	}

	void readAllUserNode() {
		userNode* current = head;
		cout << "-----------------------------------------" << endl;
		while (current != nullptr) {
			current = current->NextAddress;
		}
		cout << "-----------------------------------------" << endl;
	}

	void updateUserNode(
		string userId,
		string userName,
		string name,
		int age,
		string password,
		string gender,
		string email,
		string contact,
		string lastLogin) {
		userNode* currentNode = head;
		while (currentNode != nullptr && currentNode->UserId != userId) {
			currentNode = currentNode->NextAddress;
		}
		if (currentNode == nullptr) {
			cout << "User with ID " << userId << " not found." << endl;
		} else {
			currentNode->userUserName = userName;
			currentNode->UserName = name;
			currentNode->UserAge = age;
			currentNode->UserPassword = password;
			currentNode->UserGender = gender;
			currentNode->UserEmail = email;
			currentNode->UserContact = contact;
			currentNode->UserLastLogin = lastLogin;
			cout << "User details updated successfully." << endl;
		}
	}

	void deleteUserNode(string userId) {
		userNode* temp = head;
		bool isDeleted = false;

		// If the list is empty, nothing to delete
		if (head == nullptr) {
			cout << "List is empty. Deletion failed." << endl;
			return;
		}

		// If the head node contains the userId
		if (head->UserId == userId) {
			head = head->NextAddress;
			if (head == nullptr) {
				tail = nullptr;
			} else {
				head->PrevAddress = nullptr;
			}
			delete temp;
			isDeleted = true;
		} else {
			while (temp != nullptr) {
				if (temp->UserId == userId) {
					// If the node to delete is the tail node
					if (temp == tail) {
						tail = tail->PrevAddress;
						tail->NextAddress = nullptr;
					}
					// If the node to delete is not the head or tail node
					else {
						temp->PrevAddress->NextAddress = temp->NextAddress;
						temp->NextAddress->PrevAddress = temp->PrevAddress;
					}
					delete temp;
					isDeleted = true;
					break;
				}
				temp = temp->NextAddress;
			}
		}

		if (isDeleted) {
			cout << "User " << userId << " deleted successfully." << endl;
		} else {
			cout << "User " << userId << " not found. Deletion failed." << endl;
		}
	}

	void displayAllUser() {
		userNode* current = head;

		// if no data
		if (head == nullptr) {
			cout << "No user data available." << endl;
			return;
		}
		cout << "=========================================================================================================="
				 << endl;
		cout << setw(6) << "UserId" << setw(15) << "Username" << setw(15) << "Name" << setw(10) << "Gender" << setw(35)
				 << "Email" << setw(12) << "Contact" << setw(6) << "Age" << setw(28) << "Last Login" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;

		while (current != nullptr) {
			stringstream ss;
			string formattedTimestamp;
			formattedTimestamp = "null";

			if (current->UserLastLogin != "null") {
				time_t timestamp = static_cast<time_t>(stoi(current->UserLastLogin));
				tm timestamp_tm{};
				if (localtime_s(&timestamp_tm, &timestamp) == 0) {
					char buffer[64];
					if (strftime(buffer, sizeof(buffer), "%c", &timestamp_tm) > 0) {
						formattedTimestamp = buffer;
					}
				}
			}

			cout << setw(6) << current->UserId << setw(15) << current->userUserName << setw(15) << current->UserName
					 << setw(10) << current->UserGender << setw(35) << current->UserEmail << setw(12) << current->UserContact
					 << setw(6) << current->UserAge << setw(28) << formattedTimestamp << endl;

			current = current->NextAddress;
		}
	}

	// Linear search algorithm to find a specific user node
	userNode* getSpecificUserNode(string userId) {
		userNode* current = head;
		while (current != nullptr) {
			if (current->UserId == userId) {
				return current;
			}
			current = current->NextAddress;
		}
		cout << "User details not found" << endl;
		// Return null when not found
		return nullptr;
	}
};
