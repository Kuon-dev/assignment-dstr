#include <iostream>
#include <string>
using namespace std;

void exitProgram() {
	cout << "Exiting program...\n";
	exit(0);
}

int handleUserInput() {
	string userInput;
	while (true) {
		cout << "\033[1;32mSelect an option (or 'q' to quit)\033[0m: ";
		cin >> userInput;

		if (userInput == "q") {
			exitProgram();
		}

		try {
			int number = stoi(userInput);
			return number;
		} catch (const invalid_argument&) {
			cout << "Error: Invalid input. Please enter an integer number." << endl;
			;
		}
	}
}

string handleUserSearch() {
	string userInput;
	cin >> userInput;
	return userInput;
}
