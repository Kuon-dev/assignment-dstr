#include <iostream>
#include <limits>
#include <string>
using namespace std;

void exitProgram() {
	cout << "Exiting program...\n";
	exit(0);
}

int handleUserInput() {
	string userInput;
	while (true) {
		cout << "\033[1;32mSelect an option \033[0m: ";
		cin >> userInput;

		try {
			int number = stoi(userInput);
			return number;
		} catch (const invalid_argument&) {
			cout << "Error: Invalid input. Please enter an integer number." << endl;
			;
		}
	}
}

string handleStringInput(string title) {
	string userInput;
	while (true) {
		cout << title << endl;
		getline(cin >> ws, userInput);

		if (userInput.length() > 60) {
			cout << "Error: input exceeds 60 characters" << endl;
			continue;
		}

		return userInput;
	}
}

int handleIntInput(string title) {
	string userInput;
	while (true) {
		cout << title << endl;
		cin >> userInput;
		cin.ignore();

		if (userInput.length() > 60) {
			cout << "Error: input exceeds 60 characters" << endl;
			return -1;
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
