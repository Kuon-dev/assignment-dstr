#include "../controllers/FavouritesController.cpp"
#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>

UniversityContoller* uniController = new UniversityContoller();
newUniMerge mergeSorter;
newQuickSort sorter;
universityList* uniData = uniController->readUniversityDatabase();

FeedbackController* feedbackController;
feedbackList* feedbackData = feedbackController->readFeedbackDatabase();

MemberController* userListController;
userList* userData = userListController->readUserDatabase();

FavouritesController* favUniController;
favUniList* favUniData = favUniController->readFavUniDatabase();
//
// foward declaration
void displaySearchUniversityMenu();
void displaySortUniversityMenu();

class UserMenu {
	public:
	userNode* currentUser;
	feedbackList* userFeedback;
	void universityMenu() {
		while (true) {
			int uniID;
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
				// quick sort algorithm so sort
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
				uniID = handleIntInput("Enter University ID to save as favourite, (Press '0' to return): ");
				if (uniID == 0) {
					cout << "Exitting..." << endl;
					break;
				};
				favUniController->createUserFavUni(uniData, favUniData, uniID, currentUser->UserId, currentUser->userUserName);
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

	void editProfile() {
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Select the option to modify" << endl;
			cout << "| 1. Username" << endl;
			cout << "| 2. Name" << endl;
			cout << "| 3. Age" << endl;
			cout << "| 4. Gender" << endl;
			cout << "| 5. Email" << endl;
			cout << "| 6. Contact" << endl;
			cout << "| 7. Password" << endl;
			cout << "| 8. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			string inputString;
			int inputInt, choice = handleUserInput();
			bool modify = true;

			switch (choice) {
			case 1:
				inputString = handleStringInput("Enter your new username (Enter 1 to return)");
				if (inputString != "1") {
					modify = userListController->validateUsername(inputString, *userData);
					if (modify) {
						// update user username only
						userData->updateUserNode(
							currentUser->UserId,
							inputString,
							currentUser->UserName,
							currentUser->UserAge,
							currentUser->UserPassword,
							currentUser->UserGender,
							currentUser->UserEmail,
							currentUser->UserContact,
							currentUser->UserLastLogin);
					}
				}
				return;
			case 2:
				inputString = handleStringInput("Enter your new name (Enter 1 to return)");
				if (inputString != "1") {
					// update user name only
					userData->updateUserNode(
						currentUser->UserId,
						currentUser->userUserName,
						inputString,
						currentUser->UserAge,
						currentUser->UserPassword,
						currentUser->UserGender,
						currentUser->UserEmail,
						currentUser->UserContact,
						currentUser->UserLastLogin);
				}
				return;
			case 3:
				inputInt = handleIntInput("Enter your new age (Enter 1 to return)");
				if (inputInt != 1) {
					// update user age only
					userData->updateUserNode(
						currentUser->UserId,
						currentUser->userUserName,
						currentUser->UserName,
						inputInt,
						currentUser->UserPassword,
						currentUser->UserGender,
						currentUser->UserEmail,
						currentUser->UserContact,
						currentUser->UserLastLogin);
				}
				return;
			case 4:
				inputString = handleStringInput("Enter your new gender (Enter 1 to return)");
				if (inputString != "1") {
					// update user gender only
					userData->updateUserNode(
						currentUser->UserId,
						currentUser->userUserName,
						currentUser->UserName,
						currentUser->UserAge,
						currentUser->UserPassword,
						inputString,
						currentUser->UserEmail,
						currentUser->UserContact,
						currentUser->UserLastLogin);
				}
				return;
			case 5:
				inputString = handleStringInput("Enter your new email (Enter 1 to return)");
				if (inputString != "1") {
					modify = userListController->validateEmail(inputString);
					if (modify) {
						// update user email only
						userData->updateUserNode(
							currentUser->UserId,
							currentUser->userUserName,
							currentUser->UserName,
							currentUser->UserAge,
							currentUser->UserPassword,
							currentUser->UserGender,
							inputString,
							currentUser->UserContact,
							currentUser->UserLastLogin);
					}
				}
				return;
			case 6:
				inputString = handleStringInput("Enter your new contact (Enter 1 to return)");
				if (inputString != "1") {
					userData->updateUserNode(
						currentUser->UserId,
						currentUser->userUserName,
						currentUser->UserName,
						currentUser->UserAge,
						currentUser->UserPassword,
						currentUser->UserGender,
						currentUser->UserEmail,
						inputString,
						currentUser->UserLastLogin);
				}
				return;
			case 7:
				inputString = handleStringInput("Enter your new password (Enter 1 to return)");
				if (inputString != "1") {
					// update user password only
					userData->updateUserNode(
						currentUser->UserId,
						currentUser->userUserName,
						currentUser->UserName,
						currentUser->UserAge,
						inputString,
						currentUser->UserGender,
						currentUser->UserEmail,
						currentUser->UserContact,
						currentUser->UserLastLogin);
				}
				return;
			case 8:
				return;
			default:
				cout << "Invalid choice. Please enter a valid choice." << endl;
			}
		}
	}

	void profileMenu() {
		// TODO: display profile
		string uniid, favid;
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
			cout << "Enter your choice (1-2): ";
			int choice = handleUserInput();
			switch (choice) {
			case 1:
				cout << "You have selected 'Edit Profile'" << endl;
				editProfile();
				break;
			case 2:
				return;
				break;
			default:
				cout << "Invalid choice, please try again." << endl;
				break;
			}
		}
	}

	private:
	void setUser(userNode* user) { this->currentUser = user; }
	void displayChoiceToSortInt(string input) {
		universityNode* head;
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Please select a sort algorithm:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| 1. Merge Sort" << endl;
			cout << "| 2. Quick Sort" << endl;

			int choice = handleUserInput();
			int page;
			bool exitPaginate = true;
			switch (choice) {
			case 1:
				// call merge sort algorithm to sort integer data
				head = uniData->getHead();
				uniData->setHead(mergeSorter.mergeSortInt(head, input));
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
				// call quick sort algorithm to sort integer data
				uniController->displayPaginated(*uniData, 1);
				uniData->setHead(sorter.quicksortInt(uniData->getHead(), uniData->getTail(), input));
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

	void displayChoiceToSortString(string input) {
		universityNode* head;
		while (true) {
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Please select a sort algorithm:" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| 1. Merge Sort" << endl;
			cout << "| 2. Quick Sort" << endl;

			int choice = handleUserInput();
			int page;
			bool exitPaginate = true;
			switch (choice) {
			case 1:
				// call merge sort algorithm to sort string data
				head = uniData->getHead();
				uniData->setHead(mergeSorter.mergeSortString(head, input));
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
				// call quick sort algorithm to sort string data
				(sorter.quicksortString(uniData->getHead(), uniData->getTail(), input));
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
};

class AdminMenu {
	public:
	userNode* currentUser;
	userNode* targetUser;

	void editUserDetails(string userID) {
		while (true) {
			targetUser = userData->getSpecificUserNode(userID);
			userData->readSpecificUserNode(userID);
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			cout << "| Select the option to modify" << endl;
			cout << "| 1. Username" << endl;
			cout << "| 2. Name" << endl;
			cout << "| 3. Age" << endl;
			cout << "| 4. Gender" << endl;
			cout << "| 5. Email" << endl;
			cout << "| 6. Contact" << endl;
			cout << "| 7. Password" << endl;
			cout << "| 8. Return" << endl;
			cout
				<< "----------------------------------------------------------------------------------------------------------"
				<< endl;
			string inputString;
			int inputInt, choice = handleUserInput();
			bool modify = true;

			switch (choice) {
			case 1:
				inputString = handleStringInput("Enter the new username (Enter 1 to return)");
				if (inputString != "1") {
					modify = userListController->validateUsername(inputString, *userData);
					if (modify) {
						// update user username only
						userData->updateUserNode(
							targetUser->UserId,
							inputString,
							targetUser->UserName,
							targetUser->UserAge,
							targetUser->UserPassword,
							targetUser->UserGender,
							targetUser->UserEmail,
							targetUser->UserContact,
							targetUser->UserLastLogin);
					}
				}
				return;
			case 2:
				inputString = handleStringInput("Enter the new name (Enter 1 to return)");
				if (inputString != "1") {
					// update user name only
					userData->updateUserNode(
						targetUser->UserId,
						targetUser->userUserName,
						inputString,
						targetUser->UserAge,
						targetUser->UserPassword,
						targetUser->UserGender,
						targetUser->UserEmail,
						targetUser->UserContact,
						targetUser->UserLastLogin);
				}
				return;
			case 3:
				inputInt = handleIntInput("Enter the new age (Enter 1 to return)");
				if (inputInt != 1) {
					// update user age only
					userData->updateUserNode(
						targetUser->UserId,
						targetUser->userUserName,
						targetUser->UserName,
						inputInt,
						targetUser->UserPassword,
						targetUser->UserGender,
						targetUser->UserEmail,
						targetUser->UserContact,
						targetUser->UserLastLogin);
				}
				return;
			case 4:
				inputString = handleStringInput("Enter the new gender (Enter 1 to return)");
				if (inputString != "1") {
					// update user gender only
					userData->updateUserNode(
						targetUser->UserId,
						targetUser->userUserName,
						targetUser->UserName,
						targetUser->UserAge,
						targetUser->UserPassword,
						inputString,
						targetUser->UserEmail,
						targetUser->UserContact,
						targetUser->UserLastLogin);
				}
				return;
			case 5:
				inputString = handleStringInput("Enter the new email (Enter 1 to return)");
				if (inputString != "1") {
					modify = userListController->validateEmail(inputString);
					if (modify) {
						// update user email only
						userData->updateUserNode(
							targetUser->UserId,
							targetUser->userUserName,
							targetUser->UserName,
							targetUser->UserAge,
							targetUser->UserPassword,
							targetUser->UserGender,
							inputString,
							targetUser->UserContact,
							targetUser->UserLastLogin);
					}
				}
				return;
			case 6:
				inputString = handleStringInput("Enter the new contact (Enter 1 to return)");
				if (inputString != "1") {
					// update user contact only
					userData->updateUserNode(
						targetUser->UserId,
						targetUser->userUserName,
						targetUser->UserName,
						targetUser->UserAge,
						targetUser->UserPassword,
						targetUser->UserGender,
						targetUser->UserEmail,
						inputString,
						targetUser->UserLastLogin);
				}
				return;
			case 7:
				inputString = handleStringInput("Enter the new password (Enter 1 to return)");
				if (inputString != "1") {
					// update user password only
					userData->updateUserNode(
						targetUser->UserId,
						targetUser->userUserName,
						targetUser->UserName,
						targetUser->UserAge,
						inputString,
						targetUser->UserGender,
						targetUser->UserEmail,
						targetUser->UserContact,
						targetUser->UserLastLogin);
				}
				return;
			case 8:
				return;
			default:
				cout << "Invalid choice. Please enter a valid choice." << endl;
			}
		}
	}

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
				input_id = handleIntInput("User ID to be modify: ");
				editUserDetails(to_string(input_id));
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
				favUniController->displayTopTenUniData();
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
	void displayFeedback() {
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
				} else if (stoi(choice)) {
					feedbackData->displayFeedbackPaginate(stoi(choice));
				}

			} catch (const invalid_argument&) {
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
			menu.userDashboard();
			return;
		};
	}
};

void userRegister() {
	while (true) {
		string name, username, email, password, gender, contact, input;
		int age;
		bool userRegister = true;
		username = handleStringInput("Enter your username (Enter 1 to return)");
		if (username != "1") {
			userRegister = userListController->validateUsername(username, *userData);
			if (userRegister) {
				name = handleStringInput("Enter your name");
				password = handleStringInput("Enter your password");
				age = handleIntInput("Enter your age");
				gender = handleStringInput("Enter your gender");
				while (true) {
					email = handleStringInput("Enter your email");
					userRegister = userListController->validateEmail(email);
					if (userRegister) break;
					else continue;
				}
				contact = handleStringInput("Enter your contact");
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
			//uniData->setHead(sorter.quicksortString(uniData->getHead(), uniData->getTail(), "Name"));
			(sorter.quicksortString(uniData->getHead(), uniData->getTail(), "Name"));
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
