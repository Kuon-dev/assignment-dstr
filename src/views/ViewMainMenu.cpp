#include "../controllers/FavouritesController.cpp"
#include "../controllers/MemberController.cpp"
#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>

UniversityContoller* uniController = new UniversityContoller();
universityQuickSort sorter;
universityList* uniData = uniController->readUniversityDatabase();

FeedbackController* feedbackController;
feedbackList* feedbackData = feedbackController->readFeedbackDatabase();

MemberController* userListController;
userList* userData = userListController->readUserDatabase();
void displaySearchUniversityMenu();
class UserMenu {
	public:
	// feedbackList* feedbackData = feedbackController->readFeedbackDatabase();
	userNode* currentUser;
	feedbackList* userFeedback;
	void userDashboard() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to the User Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. View Universities" << endl;
			cout << "2. View Favourite Universities" << endl;
			cout << "3. Send Feedback" << endl;
			cout << "4. View Submitted Feedback" << endl;
			cout << "5. Profile" << endl;
			cout << "6. Logout" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-6): ";
			int choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "You have selected 'View Universities'" << endl;
				displaySearchUniversityMenu();
				break;
			case 2:
				cout << "You have selected 'View Favourite Universities'" << endl;
				// TODO: Implement 'View Favourite Universities' functionality
				break;
			case 3:
				cout << "You have selected 'Send Feedback'" << endl;
				feedbackController->createFeedback(feedbackData, currentUser);;
				break;
			case 4:
				cout << "You have selected 'View Submitted Feedback'" << endl;
				userFeedback = feedbackController->getFeedbacksByUser(feedbackData, currentUser);
				userFeedback->displayAllFeedback();
				// TODO: Implement 'View Submitted Feedback' functionality
				break;
			case 5:
				cout << "You have selected 'Profile'" << endl;
				// TODO: Implement 'Profile' functionality
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
				cin.ignore();
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
	void setUser(userNode* user) { this->currentUser = user; }
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
				feedbackController->getFeedbacksByUser(feedbackData, currentUser);
				return;
			case 2:
				// feedbackController->createFeedback(feedbackData->getTail(), currentUser);
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

class AdminMenu {
	public:
	userNode* currentUser;

	void displayAllMember() {
		while (true) {
			// system("cls");
			userData->displayAllUser();
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "1. Modify member account details" << endl;
			cout << "2. Delete member account" << endl;
			cout << "3. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-3): ";
			int choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "You have selected 'Modify member'" << endl;
				// TODO: Implement 'Modify Member' functionality
				break;
			case 2:
				cout << "You have selected 'View all feedback'" << endl;
				// TODO: Implement 'delete member account' functionality
				break;
			case 3:
				return;
				break;
			default:
				cout << "Invalid choice, please try again." << endl;
				break;
			}
		}
	}

	void adminDashboard() {
		while (true) {
			// system("cls");
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to the Admin Dashboard" << endl;
			cout << "Please select an option:" << endl;
			cout << "1. Manage member" << endl;
			cout << "2. View all feedbacks" << endl;
			cout << "3. Generate Top 10 University" << endl;
			cout << "4. Logout" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-4): ";
			int choice = handleUserInput();

			switch (choice) {
			case 1:
				displayAllMember();
				break;
			case 2:
				cout << "You have selected 'View all feedback'" << endl;
				// TODO: Implement 'view all feedback' functionality
				break;
			case 3:
				cout << "You have selected 'Generate top 10 university'" << endl;
				// TODO: Implement 'top 10 uni' functionality
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
};


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
			uniController->searchUniMerge("Name", input, uniData);
			break;

		case 2:
			uniController->searchUniversityColumn("Rank", handleIntInput("Enter your rank query: "), uniData);
			break;

		case 3:
			cout << "Enter your query: ";
			cin >> input;
			uniController->searchUniQuick("Location", input, uniData);
			break;

		case 4:
			return;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}

userNode* authenticateUser(string username, string password) {
	userNode* temp = new userNode;
	temp->UserId = "";

	// Get the current time
	std::time_t currentTime = std::time(nullptr);
	// Convert the current time to string format
	std::string currentLoginTime = std::ctime(&currentTime);
	if (!currentLoginTime.empty() && currentLoginTime.back() == '\n') {
		currentLoginTime.erase(currentLoginTime.length() - 1);
	}
	// if the user authentication is admin
	if (username == "admin" && password == "password") {
		temp->UserId = "0";
		temp->userUserName = "admin";
		temp->UserPassword = "admin";
		temp->UserName = "admin";
		temp->UserGender = "none";
		temp->UserEmail = "none";
		temp->UserLastLogin = "none";
		temp->UserAge = 20;
		temp->UserContact = 20;
		return temp;
	} else {
		userNode* current = userData->getHead();
		// if the user account and password valid and authorized
		while (current != nullptr) {
			if (current->userUserName == username && current->UserPassword == password) {
				current->UserLastLogin = currentLoginTime;
				return current;
			}
			current = current->NextAddress;
		}
		return temp;
	};
}

void displayLoginMenu() {
	string username, password;
	char ch;
	while (true) {
		// system("cls");
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;
		cout << "| LOGIN MENU" << endl;
		cout << "| Press 0 to exit" << endl;
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;
		cout << "Username: ";
		username = "";
		cin >> username;

		// allow user to go back to main menu
		if (username == "0") {
			break;
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
		userNode* authUser = authenticateUser(username, password);
		cout << authUser->UserId;
		if (authUser->UserId == "") {
			cout << endl << endl << "Incorrect username or password. Please try again." << endl;
			system("pause");
			continue;
		} else if (authUser->UserId == "0") {
			cout << endl << endl << "Logged in successfully!" << endl;
			AdminMenu menu;
			menu.adminDashboard();
			return;
		} else { // login for user
			cout << endl << endl << "Logged in successfully!" << endl;
			UserMenu menu;
			menu.currentUser = authUser;
			menu.userDashboard();
			return;
		};
	}
};

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
		cout << "| 2. View university by name" << endl;
		cout << "| 3. Search university" << endl;
		cout << "| 4. Log in" << endl;
		cout << "| 5. Register" << endl;
		cout << "| 6. Exit" << endl;
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;

		int choice = handleUserInput();
		int page;
		string name, username, email, password, gender, input;
		int age, contact;
		bool exitPaginate = true;

		switch (choice) {
		case 1:
			uniController->displayPaginated(*uniData, 1);
			while (exitPaginate) {
				page = handleIntInput("Enter page number to skip or enter 0 to return");
				if (page == 0) exitPaginate = false;
				else {
					uniController->displayPaginated(*uniData, page);
					continue;
				}
			}
			break;
		case 2:
			uniData->setHead(sorter.quicksortString(uniData->getHead(), uniData->getTail(), "Name"));
			// sort uni by name
			break;
		case 3:
			displaySearchUniversityMenu();
			break;
		case 4:
			displayLoginMenu();
			break;
		case 5:
			name = handleStringInput("Enter your name");
			username = handleStringInput("Enter your username");
			password = handleStringInput("Enter your password");
			age = handleIntInput("Enter your age");
			gender = handleStringInput("Enter your gender");
			email = handleStringInput("Enter your email");
			contact = handleIntInput("Enter your contact");

			userListController->createNewMember(*userData, username, password, name, gender, email, age, contact);
			break;
		case 6:
			cout << "Exiting the system. Goodbye!" << endl;
			return;

		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}


