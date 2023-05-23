#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <iomanip>
#include <typeinfo>

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
	int UserContact;
	string UserLastLogin;
};

class userList {
	userNode* head = nullptr;
	userNode* tail = nullptr;

	public:

	userNode* getHead() { return this->head; }
	userNode* getTail() { return this->tail; }

	void createUserNode(
		string userId,
		string userName,
		string userPassword,
		string name,
		int age,
		string gender,
		string email,
		int contact,
		string lastLogin) {
		userNode* newUserNode = new userNode;
		newUserNode->UserId = userId;
		newUserNode->userUserName = userName;
		newUserNode->UserPassword = userPassword;
		newUserNode->UserName = name;
		newUserNode->UserAge = age;
		newUserNode->UserGender = gender;
		newUserNode->UserEmail = email;
		newUserNode->UserContact = contact;
		newUserNode->UserLastLogin = lastLogin;
		newUserNode->PrevAddress = nullptr;
		newUserNode->NextAddress = nullptr;
		if (head == nullptr) {
			head = tail = newUserNode;
		} else {
			tail->NextAddress = newUserNode;
			newUserNode->PrevAddress = tail;
			tail = newUserNode;
		};
	}

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
		string userId, string userName, string name, int age, string gender, string email, int contact, string lastLogin) {
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
		if (head == nullptr) {
			cout << "----------------------------------------------------------------------------------------------------------" << endl;
			cout << "There is no user account." << endl;
			cout << "----------------------------------------------------------------------------------------------------------" << endl;
			return;
		}

		userNode* current = head;
		
		cout << "----------------------------------------------------------------------------------------------------------" << endl;
		while (current != nullptr) {
			cout  << left << setw(15) << current->UserId << setw(15) << current->userUserName << setw(50)
						<< current->UserName << endl;
			current = current->NextAddress;
		}
		cout << "----------------------------------------------------------------------------------------------------------" << endl;
	}

	private:
};
