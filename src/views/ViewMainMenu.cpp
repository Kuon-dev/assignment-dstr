#include "../Modules/InputHandler.cpp"
#include "./ViewLoginMenu.cpp"

void displaySearchUniversityMenu() {
	UniversityContoller uniController;
	FavouritesController fav;
	fav.getFULinkListFromDB();
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
			uniController.searchUniversityColumn("Name", input);
			break;

		case 2:
			cout << "Enter your query: ";
			cin >> input;
			uniController.searchUniversityColumn("Rank", input);
			break;

		case 3:
			cout << "Enter your query: ";
			cin >> input;
			uniController.searchUniversityColumn("Location", input);
			break;

		case 4:
			return;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}

void displayMenu() {
	UniversityContoller uniController;

	while (true) {
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| Please select an option:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "| 1. View all universities" << endl;
		cout << "| 2. View university by rank" << endl;
		cout << "| 3. Log in" << endl;
		cout << "| 4. Exit" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;

		int choice = handleUserInput();

		switch (choice) {
		case 1:
			uniController.displayFist20Uni();
			break;
		case 2:
			displaySearchUniversityMenu();
			break;
		case 3:
			displayLoginMenu();
			break;
		case 4:
			cout << "Exiting the system. Goodbye!" << endl;
			return;
		default:
			cout << "Invalid choice. Please enter a valid choice." << endl;
		}
	}
}
