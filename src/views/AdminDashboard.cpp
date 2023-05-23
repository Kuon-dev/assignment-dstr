#include "../models/Member.cpp"

#include <iostream>
#include <string>

using namespace std;

class AdminMenu {
	public:
	void dashboard() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to the User Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. Feedback" << endl;
			cout << "2. View Universities" << endl;
			cout << "3. View all users" << endl;
			cout << "4. Logout" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-5): ";
			int choice;
			cin >> choice;

			switch (choice) {
			case 1:
				cout << "You have selected 'View Replied Feedback'" << endl;
				// TODO: Implement 'View Replied Feedback' functionality
				break;
			case 2:
				cout << "You have selected 'View Universities'" << endl;
				// TODO: Implement 'View Universities' functionality
				break;
			case 3:
				cout << "You have selected 'View all users'" << endl;
				// userList userFunc = readUserDatabase();
				// userFunc.displayAllUser();
				break;
			case 4:
				cout << "You have selected 'Logout'" << endl;
				cout << "Goodbye!" << endl;
				return;
			default:
				cout << "Invalid choice, please try again." << endl;
				break;
			}
		}
	}

	void feedbackMenu() {
		// TODO: list feedback
		// TODO: search feedback
		// TODO: reply feedback
	}

	void universityMenu() {
		// TODO: search university
		// TODO: list uni
		// TODO: select uni as fav
	}

	void profileMenu() {
		// TODO: display profile
		// TODO: edit profile
		// TODO: view favourite uni
	}

	private:
};
