#include "../models/Member.cpp"

#include <iostream>
#include <string>

using namespace std;

class UserMenu {

	UserMenu(){
		userNode * currentUser;
	}

	public:
	void userDashboard(){
		while (true) {
			cout << "----------------------------------------------------------------------------------------------------------" << endl;
			cout << "Welcome to the User Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. Feedback" << endl;
			cout << "2. View Universities" << endl;
			cout << "3. Profile" << endl;
			cout << "4. Logout" << endl;
			cout << "----------------------------------------------------------------------------------------------------------" << endl;
			cout << "Enter your choice (1-5): ";
			int choice;
			cin >> choice;

			switch (choice) {
				case 1:
					cout << "You have selected 'Leave Feedback'" << endl;
					// TODO: Implement 'Leave Feedback' functionality
					break;
				case 2:
					cout << "You have selected 'View Replied Feedback'" << endl;
					// TODO: Implement 'View Replied Feedback' functionality
					break;
				case 3:
					cout << "You have selected 'View Universities'" << endl;
					// TODO: Implement 'View Universities' functionality
					break;
				case 4:
					cout << "You have selected 'Edit Profile'" << endl;
					// TODO: Implement 'Edit Profile' functionality
					break;
				case 5:
					cout << "You have selected 'Logout'" << endl;
					cout << "Goodbye!" << endl;
					return;
				default:
					cout << "Invalid choice, please try again." << endl;
					break;
			}
		}

	}

	void feedbackMenu(){
		// TODO: leave a feedback
		// TODO: look at feedback reply
	}

	void universityMenu(){
		// TODO: search university
		// TODO: list uni
		// TODO: select uni as fav
	}

	void profileMenu(){
		// TODO: display profile
		// TODO: edit profile
		// TODO: view favourite uni

	}

	private:

};


