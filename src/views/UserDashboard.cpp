//#include <conio.h>
//#include <iostream>
//#include <string>
//#include "../controllers/FavouritesController.cpp"
//
//
//using namespace std;
//
//class UserMenu {
//	//UserMenu() { userNode* current; }
//
//	public:
//	void userDashboard() {
//		while (true) {
//			cout
//				<< "----------------------------------------------------------------------------------------------------------"
//				<< endl;
//			cout << "Welcome to the User Dashboard" << endl;
//			cout << "Please select an option:" << endl;
//			cout << "1. Feedback" << endl;
//			cout << "2. View Universities" << endl;
//			cout << "3. Profile" << endl;
//			cout << "4. Logout" << endl;
//			cout
//				<< "----------------------------------------------------------------------------------------------------------"
//				<< endl;
//			cout << "Enter your choice (1-5): ";
//			int choice;
//			cin >> choice;
//
//			switch (choice) {
//			case 1:
//				cout << "You have selected 'Leave Feedback'" << endl;
//				// TODO: Implement 'Leave Feedback' functionality
//				break;
//			case 2:
//				cout << "You have selected 'View Replied Feedback'" << endl;
//				// TODO: Implement 'View Replied Feedback' functionality
//				break;
//			case 3:
//				cout << "You have selected 'View Universities'" << endl;
//				// TODO: Implement 'View Universities' functionality
//				break;
//			case 4:
//				cout << "You have selected 'Edit Profile'" << endl;
//				// TODO: Implement 'Edit Profile' functionality
//				break;
//			case 5:
//				cout << "You have selected 'Logout'" << endl;
//				cout << "Goodbye!" << endl;
//				return;
//			default:
//				cout << "Invalid choice, please try again." << endl;
//				break;
//			}
//		}
//	}
//
//	void feedbackMenu() {
//		// TODO: leave a feedback
//		// TODO: look at feedback reply
//	}
//
//	void universityMenu() {
//		// TODO: search university
//		// TODO: list uni
//		// TODO: select uni as fav
//	}
//
//	void profileMenu() {
//		// TODO: display profile
//		// 
//		// TODO: edit profile
//		// TODO: view favourite uni
//
//		//variables to be assigned later
//		string uniid, userid, favid;
//
//		//create object favCont of FavouritesController class
//		FavouritesController favCont;
//
//		//get complete data from favuni data set
//		favCont.getFULinkListFromDB();
//
//		cout << "User ID: ";
//		getline(cin, userid);
//
//		favUniNode* test = favCont.readFavDatabase(userid);
//
//		//display uni list based on user id
//
//		cout
//			<< "----------------------------------------------------------------------------------------------------------"
//			<< endl;
//
//		cout << "List of Favourite University" << endl;
//
//		cout
//			<< "----------------------------------------------------------------------------------------------------------"
//			<< endl;
//
//		favCont.displayFavUni(test);
//
//
//		cout<< endl;
//
//		while (true) {
//			cout
//				<< "----------------------------------------------------------------------------------------------------------"
//				<< endl;
//			cout << "Welcome to Profile Dashboard" << endl;
//			cout << "Please select an option:" << endl;
//			cout << "1. View Profile" << endl;
//			cout << "2. Edit Profile" << endl;
//			cout << "3. View Favourite Universities" << endl;
//			cout << "4. Add Favourite Universities" << endl;
//			cout << "5. Delete Favourite Universities" << endl;
//			cout << "6. Logout" << endl;
//			cout
//				<< "----------------------------------------------------------------------------------------------------------"
//				<< endl;
//			cout << "Enter your choice (1-5): ";
//			int choice;
//			cin >> choice;
//
//			
//
//			//favUniNode* test = favCont.readFavDatabase(userid);
//
//			////display uni list based on user id
//			//favCont.displayFavUni(test);
//
//			switch (choice) {
//			case 1:
//				cout << "You have selected 'View Profile'" << endl;
//				// TODO: Implement 'View Profile' functionality
//				break;
//			case 2:
//				cout << "You have selected 'Edit Profile'" << endl;
//				// TODO: Implement 'Edit Profile' functionality
//				break;
//			case 3:
//				cout << "You have selected 'View Favourite Universities'" << endl;
//				// TODO: Implement 'View Favourite Universities' functionality
//				
//				
//
//				//display uni list based on user id
//				favCont.displayFavUni(test);
//					
//
//				break;
//			case 4:
//				cout << "You have selected 'Add Favourite Universities'" << endl;
//				// TODO: Implement 'Add Favourite Universities' functionality
//
//				cin.ignore();
//				cout << "University ID: ";
//				getline(cin, uniid);
//
//				favCont.createUserFavUni(uniid);
//				
//
//				break;
//			case 5:
//				cout << "You have selected 'Delete Favourite Universities'" << endl;
//				// TODO: Implement 'Delete Favourite Universities' functionality
//
//				//favCont.displayFavUni(test);
//
//
//				cout << "Fav Uni List ID: ";
//				cin>>favid;
//
//				
//				favCont.deleteBasedOnFavUni(favid);
//				//favCont.displayFavUni(favCont.getHead());
//
//				break;
//			case 6:
//				cout << "You have selected 'Logout'" << endl;
//				cout << "Goodbye!" << endl;
//				return;
//			default:
//				cout << "Invalid choice, please try again." << endl;
//				break;
//			}
//		}
//
//		//code which display report for top 10 fav university 
//		//favCont.displayTopTenUniData();
//
//		/*cout << "University ID: ";
//		getline(cin, uniid);*/
//
//		/*cout << "User ID: ";
//		getline(cin, userid);*/
//
//		/*cout << "Fav Uni List ID: ";
//		getline(cin, favid);*/
//
//		// display all fav uni list
//		//favCont.displayFavUni(favCont.getHead());
//
//
//		//favCont.createUserFavUni(uniid);
//		//favUniNode* test = favCont.readFavDatabase("987");
//		//favCont.deleteBasedOnFavUni(favid);
//		//favCont.displayFavUni(favCont.getHead());
//
//		////system("cls");
//
//		//
//		//
//		//test = favCont.readFavDatabase("987");
//		//favCont.displayFavUni(favCont.getHead());
//
//
//
//
//
//		
//	}
//
//	private:
//};
