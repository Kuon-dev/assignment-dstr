#include "../Controllers/UniversityController.cpp"
#include "./ViewLoginMenu.cpp"

void displayMenu() {
	int choice;
	universityList uniList;
	UniversityContoller uniController;

	while (true) {
		cout << "Please select an option:" << endl;
		cout << "1. View all universities" << endl;
		cout << "2. View university by rank" << endl;
		cout << "3. Log in" << endl;
		cout << "4. Exit" << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			uniController.displayFist20Uni();
			// Call function to display all universities
			break;
		case 2:
			uniController.dispalyFirst20UniSorted();
			// Call function to display university by rank
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
