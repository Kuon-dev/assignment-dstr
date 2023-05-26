#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "../controllers/FeedbackController.cpp"

using namespace std;

class MemberController {
	public:
	// read users database from Users.csv
	userList* readUserDatabase() {
		userList* list = new userList();
		ifstream file("Database/Users.csv"); // get user database
		// validate file open
		if (!file.is_open()) {
			cout << "\033[31m"
					 << "Error: could not open user file "
					 << "\033[0m" << endl;
			return list;
		}
		// define database haeder and line
		string header, line;
		getline(file, header);

		while (getline(file, line)) {
			stringstream iss(line);
			userNode* node = new userNode();

			string UserId, userUserName, UserPassword, UserName, UserGender, UserEmail, UserLastLogin;
			int UserAge, UserContact;

			string token; // to get value

			getline(iss, token, ',');
			UserId = token;

			getline(iss, token, ',');
			userUserName = token;

			getline(iss, token, ',');
			UserPassword = token;

			getline(iss, token, ',');
			UserName = token;

			getline(iss, token, ',');
			UserGender = token;

			getline(iss, token, ',');
			UserEmail = token;

			getline(iss, token, ',');
			UserLastLogin = token;

			getline(iss, token, ',');
			UserAge = stoi(token);

			getline(iss, token, ',');
			UserContact = stoi(token);

			node->UserId = UserId;
			node->userUserName = userUserName;
			node->UserPassword = UserPassword;
			node->UserName = UserName;
			node->UserGender = UserGender;
			node->UserEmail = UserEmail;
			node->UserLastLogin = UserLastLogin;
			node->UserAge = UserAge;
			node->UserContact = UserContact;

			list->addUserNode(node);
		};

		file.close();
		return list;
	};

	void readAllUserNode() {
		userList list;
		list.readAllUserNode();
	}

	// check username special characters and unique
	bool validateUsername(const string& username, const userList& users, userNode* headNode) {
		// Regular expression pattern for username without special characters
		regex pattern("^[a-zA-Z0-9_]+$");
		userNode* current = headNode;

		// Check if the username matches the pattern
		if (!regex_match(username, pattern)) {
			cout << "Invalid username. Username should only contain alphanumeric characters and underscore (_)." << endl;
			return false;
		}

		// validate username length
		if (username.length() > 60) {
			cout << "Error: input exceeds 60 characters" << endl;
			return false;
		}
		cout << "username" << username;
		// cout << "userlist " << (users.length() ? "got" : "no") << endl;

		// Check if the username already exists in the user list
		while (current != nullptr) {
			// if (current->userUserName == username) {
			// 	cout << "Username already exists. Please choose a different username." << endl;
			// 	return false;
			// }
			current = current->NextAddress;
		}

		// Username is valid
		return true;
	}

	// create a new user node and append to csv
	void createNewMember(
		userList data, string username, string password, string name, string gender, string email, int age, int contact) {
		userNode* newUser = new userNode();
		userList* list = new userList();
		newUser->UserId = to_string(createUserId(data));
		newUser->userUserName = username;
		newUser->UserPassword = password;
		newUser->UserName = name;
		newUser->UserAge = age;
		newUser->UserGender = gender;
		newUser->UserEmail = email;
		newUser->UserContact = contact;
		newUser->UserLastLogin = "null";

		ofstream outfile("Database/Users.csv", ios::app);
		if (outfile) {
			outfile << newUser->UserId << "," << newUser->userUserName << "," << newUser->UserPassword << ","
							<< newUser->UserName << "," << newUser->UserGender << "," << newUser->UserEmail << ","
							<< newUser->UserLastLogin << "," << to_string(newUser->UserAge) << "," << to_string(newUser->UserContact)
							<< endl;

			outfile.close();

			data.addUserNode(newUser);

			cout << "User acccount created." << endl;
		} else {
			cout << "Please try again later." << endl;
		}

		// after write data into excel need to append to the linked list
		// assign new user as tail then the previous node need change
		// try this when display all user list
	}

	private:
	int createUserId(userList data) {
		userNode* lastNode = data.getTail();
		if (lastNode == nullptr) return 1;
		else if (lastNode->UserId == "") return 1;
		else return (stoi(lastNode->UserId) + 1);
	}
};
