#include "../controllers/FavouritesController.cpp"
#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>

UniversityContoller* uniController = new UniversityContoller();
universityMergeSort mergeSorter;
universityQuickSort sorter;
universityList* uniData = uniController->readUniversityDatabase();

FeedbackController* feedbackController;
feedbackList* feedbackData = feedbackController->readFeedbackDatabase();

MemberController* userListController;
userList* userData = userListController->readUserDatabase();

FavouritesController* favUniController;
favUniList* favUniData = favUniController->readFavUniDatabase();

void displaySearchUniversityMenu();
void displaySortUniversityMenu();
class UserMenu {
	public:
	userNode* currentUser;
	feedbackList* userFeedback;
	void universityMenu() {
		while (true) {
			string uniID;
			int page;
			bool exitPaginate = true;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Please select an option:" << endl;
			cout << "1. View the Top Score University" << endl;
			cout << "2. Save University as Favourite" << endl;
			cout << "3. Sort University" << endl;
			cout << "4. Search University" << endl;
			cout << "5. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (1-5): ";
			int choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "You have selected 'View the Top Score University'" << endl;
				//quick sort algorithm so sort
				sorter.quicksortInt(uniData->getHead(), uniData->getTail(), "ScoreScaled");
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
				cout << "You have selected 'Save University as Favourite'" << endl;
				cin.ignore();
				cout << "University ID to save: ";
				getline(cin, uniID);
				favUniController->createUserFavUni(uniID, currentUser->UserId, currentUser->userUserName);
				break;
			case 3:
				displaySortUniversityMenu();
				break;
			case 4:
				displaySearchUniversityMenu();
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

	void userDashboard() {
    favUniList* getUserFavUni;
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
				universityMenu();
				break;
			case 2:
				getUserFavUni = favUniController->getUserFav(favUniData, currentUser);
				cout << "You have selected 'View Favourite Universities'" << endl;
				getUserFavUni->displayAll();
				break;
			case 3:
				cout << "You have selected 'Send Feedback'" << endl;
				feedbackController->createFeedback(feedbackData, currentUser);
				;
				break;
			case 4:
				cout << "You have selected 'View Submitted Feedback'" << endl;
				userFeedback = feedbackController->getFeedbacksByUser(feedbackData, currentUser);
				userFeedback->displayAllFeedback();
				break;
			case 5:
				cout << "You have selected 'Profile'" << endl;
				profileMenu();
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
		string uniid, favid, testusername, testuserid;

		// setUser(userNode * user);
		// cout << currentUser->UserId << endl;
		//testuserid = /*userListController.returnUserId(currentUser)*/ "987";
		//testusername = /*userListController.returnUserName(currentUser)*/ "Loong";

		testuserid = currentUser->UserId;
		testusername = currentUser->userUserName;

		FavouritesController favCont;
		favCont.getFULinkListFromDB();
		favUniNode* test = favCont.readFavDatabase(testuserid);

		// cout << "User ID: ";
		// getline(cin, testuserid);


		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Welcome to Profile Dashboard" << endl;
			userData->readSpecificUserNode(currentUser->UserId);
			cout << "Please select an option:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "1. Edit Profile" << endl;
			cout << "2. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "Enter your choice (0-1): ";
			int choice = handleUserInput();
			switch (choice) {
			case 1:
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
				cout << endl;
				cout << "Please enter the University ID to be saved as Fvaourite University: ";
				getline(cin, uniid);
				favCont.createUserFavUni(uniid, testuserid, testusername);
				break;
			case 5:
				cout << "You have selected 'Delete Favourite Universities'" << endl;
				// TODO: Implement 'Delete Favourite Universities' functionality
				// favCont.displayFavUni(test);
				cout << "Please enter the Record ID for Favourite University to be deleted: ";
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
};

class AdminMenu {
	public:
	userNode* currentUser;
	FavouritesController favCont;

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
			int input_id, choice = handleUserInput();

			switch (choice) {
			case 1:
				cout << "You have selected 'Modify member'" << endl;
				// TODO: Implement 'Modify Member' functionality
				break;
			case 2:
				cout << "You have selected 'Delete member account'" << endl;
				input_id = handleIntInput("User ID to be deleted: ");
				userData->deleteUserNode(to_string(input_id));
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
				displayFeedback();
				break;
			case 3:
				cout << "You have selected 'Generate top 10 university'" << endl;
				favCont.displayTopTenUniData();
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

	private:
	void displayFeedback(){
		while (true) {
			feedbackData->displayFeedbackPaginate(1);
			string choice = handleStringInput("Press 0 to return, Press 'a' to reply feedback, Enter number to go to page");
			string feedback;
			string replyContent;
			feedbackNode* getFeedback;
			try {
				if (choice == "0") return;
				else if (choice == "a") {
					feedback = handleStringInput("Enter feedback ID to reply, press 0 to return: ");
					if (feedback == "0") return;
					getFeedback = feedbackData->getFeedbackById(feedback);
					if (getFeedback == nullptr) return;

					feedbackData->displayFeedback(getFeedback);
					replyContent = handleStringInput("Enter your reply, press 0 to return: ");
					if (replyContent == "0") return;
					feedbackData->updateFeedbackReply(getFeedback, replyContent);
				}
				else if (stoi(choice)){
					feedbackData->displayFeedbackPaginate(stoi(choice));
				}

			}
			catch(const invalid_argument&) {
				cout << "Invalid input";
			};
		}
	};
};

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
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| LOGIN MENU" << endl;
		cout << "| Press 0 to exit" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
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
			//menu.userDashboard();
			menu.profileMenu();
			return;
		};
	}
};

void userRegister() {
	while (true) {
		string name, username, email, password, gender, input;
		int age, contact;
		bool userRegister = true;
		username = handleStringInput("Enter your username (Enter 1 to return)");
		if (username != "1") {
			userRegister = userListController->validateUsername(username, *userData);
			if (userRegister) {
				name = handleStringInput("Enter your name");
				password = handleStringInput("Enter your password");
				age = handleIntInput("Enter your age");
				gender = handleStringInput("Enter your gender");
				email = handleStringInput("Enter your email");
				userRegister = userListController->validateEmail(email);
			}
			if (userRegister) {
				contact = handleIntInput("Enter your contact");
				userRegister = userListController->validateContact(to_string(contact));
			}
			if (userRegister) {
				userListController->createNewMember(*userData, username, password, name, gender, email, age, contact);
				break;
			};
		} else return;
	}
}

void displaySearchUniversityMenu() {
	FavouritesController favouriteData;
	// favouriteData.getFULinkListFromDB();
	while (true) {
		string input;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| Please select an option:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| 1. Search University by name" << endl;
		cout << "| 2. Search University by rank" << endl;
		cout << "| 3. Search University by country" << endl;
		cout << "| 4. Exit" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
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

void displayChoiceToSortString(string input) {
	universityNode* head;
	while (true) {
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| Please select a sort algorithm:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| 1. Merge Sort" << endl;
		cout << "| 2. Quick Sort" << endl;

		int choice = handleUserInput();
		int page;
		bool exitPaginate = true;
		switch (choice) {
		case 1:
			//call merge sort algorithm to sort string data
			head = uniData->getHead();
			uniData->setHead(mergeSorter.mergeSortUniversityString(&head, input));
			uniController->displayPaginated(*uniData, 1);
			while (exitPaginate) {
				page = handleIntInput("Enter page number to skip or enter 0 to return");
				if (page == 0) exitPaginate = false;
				else {
					uniController->displayPaginated(*uniData, page);
					continue;
				}
			}
			return;
		case 2:
			//call quick sort algorithm to sort string data
			uniData->setHead(sorter.quicksortString(uniData->getHead(), uniData->getTail(), input));
			uniController->displayPaginated(*uniData, 1);
			while (exitPaginate) {
				page = handleIntInput("Enter page number to skip or enter 0 to return");
				if (page == 0) exitPaginate = false;
				else {
					uniController->displayPaginated(*uniData, page);
					continue;
				}
			}
			return;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}

void displayChoiceToSortInt(string input) {
	universityNode* head;
	while (true) {
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| Please select a sort algorithm:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| 1. Merge Sort" << endl;
		cout << "| 2. Quick Sort" << endl;

		int choice = handleUserInput();
		int page;
		bool exitPaginate = true;
		switch (choice) {
		case 1:
			//call merge sort algorithm to sort integer data
			head = uniData->getHead();
			uniData->setHead(mergeSorter.mergeSortUniversityInt(&head, input));
			uniController->displayPaginated(*uniData, 1);
			while (exitPaginate) {
				page = handleIntInput("Enter page number to skip or enter 0 to return");
				if (page == 0) exitPaginate = false;
				else {
					uniController->displayPaginated(*uniData, page);
					continue;
				}
			}
			return;
		case 2:
			//call quick sort algorithm to sort integer data
			uniController->displayPaginated(*uniData, 1);
			sorter.quicksortInt(uniData->getHead(), uniData->getTail(), input);
			while (exitPaginate) {
				page = handleIntInput("Enter page number to skip or enter 0 to return");
				if (page == 0) exitPaginate = false;
				else {
					uniController->displayPaginated(*uniData, page);
					continue;
				}
			}
			return;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}

void displaySortUniversityMenu() {
	while (true) {
		string input;
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;
		cout << "| Please select an option:" << endl;
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;
		cout << "| 1. Sort University by name" << endl;
		cout << "| 2. Sort University by rank" << endl;
		cout << "| 3. Sort University by location" << endl;
		cout << "| 4. Sort University by Academic reputation score" << endl;
		cout << "| 5. Sort University by Employer reputation score" << endl;
		cout << "| 6. Sort University by Faculty/student ratio score" << endl;
		cout << "| 7. Sort University by Citations per faculty" << endl;
		cout << "| 8. Sort University by International faculty ratio" << endl;
		cout << "| 9. Sort University by International student ratio" << endl;
		cout << "| 10. Sort University by International research network" << endl;
		cout << "| 11. Sort University by Employment outcome" << endl;
		cout << "| 12. Return" << endl;
		cout
			<< "----------------------------------------------------------------------------------------------------------"
			<< endl;

		int choice = handleUserInput();

		switch (choice) {
		case 1:
			displayChoiceToSortString("Name");
			break;
		case 2:
			displayChoiceToSortInt("Rank");
			break;
		case 3:
			displayChoiceToSortString("Location");
			break;
		case 4:
			displayChoiceToSortInt("ArRank");
			break;
		case 5:
			displayChoiceToSortInt("ErRank");
			break;
		case 6:
			displayChoiceToSortInt("FsrRank");
			break;
		case 7:
			displayChoiceToSortInt("CpfRank");
			break;
		case 8:
			displayChoiceToSortInt("IfrRank");
			break;
		case 9:
			displayChoiceToSortInt("IsrRank");
			break;
		case 10:
			displayChoiceToSortInt("IrnRank");
			break;
		case 11:
			displayChoiceToSortInt("GerRank");
			break;
		case 12:
			return;
			break;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}

void displayMenu() {
	while (true) {
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| Please select an option:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| 1. View all universities" << endl;
		cout << "| 2. View university by name" << endl;
		cout << "| 3. Search university" << endl;
		cout << "| 4. Log in" << endl;
		cout << "| 5. Register" << endl;
		cout << "| 6. Exit" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
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
			userRegister();
			break;
		case 6:
			cout << "Exiting the system. Goodbye!" << endl;
			return;

		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}
