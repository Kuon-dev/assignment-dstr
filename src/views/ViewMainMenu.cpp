#include "../controllers/FavouritesController.cpp"
#include "../controllers/MemberController.cpp"
#include <conio.h>
#include <iostream>
#include <string>

UniversityContoller uniController;
universityList uniData = uniController.readUniversityDatabase();
MemberController userListController;
userList userData = userListController.readUserDatabase();

class UserMenu {
	public:
	userNode *currentUser;
	UserMenu(userNode* currentUser){
		this->currentUser = currentUser;
	};
	FeedbackController feedbackController;
	void userDashboard() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to the User Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. Leave a Feedback" << endl;
			cout << "2. View Universities" << endl;
			cout << "3. Profile" << endl;
			cout << "4. Logout" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-5): ";
			int choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "You have selected 'Leave Feedback'" << endl;
				// TODO: Implement 'Leave Feedback' functionality
				break;
			case 2:
				cout << "You have selected 'View Universities'" << endl;
				// TODO: Implement 'View Universities' functionality
				break;
			case 3:
				cout << "You have selected 'Edit Profile'" << endl;
				// TODO: Implement 'Edit Profile' functionality
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
		// TODO: leave a feedback
		// TODO: look at feedback reply
	}

	void universityMenu() {
		// TODO: search university
		// TODO: list uni
		// TODO: select uni as fav
	}

	void profileMenu() {
		// TODO: display profile
		string uniid, userid, favid;
		FavouritesController favCont;
		favCont.getFULinkListFromDB();

		cout << "User ID: ";
		getline(cin, userid);

		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to Profile Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. View Profile" << endl;
			cout << "2. Edit Profile" << endl;
			cout << "3. View Favourite Universities" << endl;
			cout << "4. Add Favourite Universities" << endl;
			cout << "5. Delete Favourite Universities" << endl;
			cout << "6. Logout" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-5): ";
			int choice = handleUserInput();

			favUniNode* test = favCont.readFavDatabase(userid);
			switch (choice) {
			case 1:
				cout << "You have selected 'View Profile'" << endl;
				// TODO: Implement 'View Profile' functionality
				FeedbackDisplayUser();
				break;
			case 2:
				cout << "You have selected 'Edit Profile'" << endl;
				// TODO: Implement 'Edit Profile' functionality
				break;
			case 3:
				cout << "You have selected 'View Favourite Universities'" << endl;
				// TODO: Implement 'View Favourite Universities' functionality
				// display uni list based on user id
				favCont.displayFavUni(test);
				break;
			case 4:
				cout << "You have selected 'Add Favourite Universities'" << endl;
				// TODO: Implement 'Add Favourite Universities' functionality
				cout << "University ID: ";
				getline(cin, uniid);
				favCont.createUserFavUni(uniid);
				break;
			case 5:
				cout << "You have selected 'Delete Favourite Universities'" << endl;
				// TODO: Implement 'Delete Favourite Universities' functionality
				// favCont.displayFavUni(test);
				cout << "Input the University You want to Delete: ";
				cin >> favid;
				favCont.deleteBasedOnFavUni(favid);
				// favCont.displayFavUni(favCont.getHead());
				break;
			case 6:
				cout << "You have selected 'Logout'" << endl;
				cout << "Goodbye!" << endl;
				return;
			default:
				cout << "Invalid choice, please try again." << endl;
				break;
			}
		}
	}

	private:
	void setUser(userNode *user){
		this->currentUser = user;
	}
	void FeedbackDisplayUser() {
		int choice;
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Feedback Dashboard" << endl;
			cout << "1. Select feedback" << endl;
			cout << "2. Leave a new feedback" << endl;
			cout << "3. Exit" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;

			choice = handleUserInput();
			switch (choice) {
			case 1:
					feedbackController.readFeedbackByUser(userNode *user)
				return;
			case 2:
				feedbackController.createFeedback();
				break;
			case 3:
				cout << "Exiting..." << endl;
				return;
			default:
				cout << "Invalid choice" << endl;
				break;
			}
		}
	}

	void FeedbackCreateConfirm() {
		int choice;
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "1. Confirm leave a new feedback?" << endl;
			cout << "2. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			choice = handleUserInput();
			switch (choice) {
			case 1:
				// Handle leaving new feedback confirmation
				// ...
				return;
			case 2:
				return;
			default:
				cout << "Invalid choice" << endl;
				break;
			}
		}
	}
};

class GuestMenu {
	public:
	void displaySearchUniversityMenu() {
		FavouritesController favouriteData;
		favouriteData.getFULinkListFromDB();
		while (true) {
			string input;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Please select an option:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| 1. Search University by name" << endl;
			cout << "| 2. Search University by rank" << endl;
			cout << "| 3. Search University by country" << endl;
			cout << "| 4. Exit" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;

			int choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "Enter your query: ";
				cin >> input;
				uniController.searchUniMerge("Name", input);
				break;

			case 2:
				uniController.searchUniversityColumn("Rank", handleIntInput("Enter your rank query: "));
				break;

			case 3:
				cout << "Enter your query: ";
				cin >> input;
				uniController.searchUniQuick("Location", input);
				break;

			case 4:
				return;
			default:
				cout << "Invalid choice. Please enter a valid choice." << endl;
			}
		}
	}

	void displayMenu() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Please select an option:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| 1. View all universities" << endl;
			cout << "| 2. View university by rank" << endl;
			cout << "| 3. Log in" << endl;
			cout << "| 4. Register" << endl;
			cout << "| 5. Exit" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;

			int choice = handleUserInput();
			int page;
			string name, username, email, password, gender;
			int age, contact;
			bool exitPaginate = true;

			switch (choice) {
			case 1:
				uniController.displayPaginated(uniData, 1);
				while (exitPaginate) {
					page = handleIntInput("Enter page number to skip or enter 0 to return");
					if (page == 0) exitPaginate = false;
					else {
						uniController.displayPaginated(uniData, page);
						continue;
					}
				}
				break;
			case 2:
				displaySearchUniversityMenu();
				break;
			case 3:
				displayLoginMenu();
				break;
			case 4:
				name = handleStringInput("Enter your name");
				username = handleStringInput("Enter your username");
				password = handleStringInput("Enter your password");
				age = handleIntInput("Enter your age");
				gender = handleStringInput("Enter your gender");
				email = handleStringInput("Enter your email");
				contact = handleIntInput("Enter your contact");

				userListController.createNewMember(userData, username, password, name, gender, email, age, contact);
				break;
			case 5:
				cout << "Exiting the system. Goodbye!" << endl;
				return;

			default:
				cout << "Invalid choice. Please enter a valid choice." << endl;
			}
		}
	}

	void displayFeedbackMenu() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Please select an option:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| 1. View all universities" << endl;
			cout << "| 2. View university by rank" << endl;
			cout << "| 3. Log in" << endl;
			cout << "| 4. Register" << endl;
			cout << "| 5. Exit" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
		}
	}

	void displayLoginMenu() {
		string username, password;
		char ch;

		while (true) {
			system("cls");
			cout << "-------------------------" << endl;
			cout << "| LOGIN MENU" << endl;
			cout << "| Press 0 to exit" << endl;
			cout << "------------------------" << endl;
			cout << "Username: ";
			username = "";
			cin >> username;

			// allow user to go back to main menu
			if (username == "0") {
				return;
			}

			cout << "Password: ";
			// disable console output for password input
			ch = _getch();
			password = "";
			while (ch != 13) {
				if (ch == 8) {
					if (password.length() > 0) {
						password.pop_back();
						cout << "\b \b";
					}
				} else {
					password += ch;
					cout << "*";
				}
				ch = _getch();
			}

			if (authenticateUser(username, password)) {
				// call loginSuccess function when credentials are correct
				cout << endl << endl << "Logged in successfully!" << endl;
				// loginSuccess();
				UserMenu menu;
				menu.profileMenu();
				return;
			} else {
				cout << endl << endl << "Incorrect username or password. Please try again." << endl;
				system("pause");
			}
		}
	}

	private:
	bool authenticateUser(string username, string password) { return (username == "admin" && password == "password"); }
};

class AdminMenu {};
