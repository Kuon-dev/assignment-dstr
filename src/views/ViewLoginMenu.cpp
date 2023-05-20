#include "../Modules/InputHandler.cpp"
#include "UserDashboard.cpp"
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

bool authenticateUser(string username, string password) {
	// hard-coded credentials for now
	return (username == "admin" && password == "password");
}

void displayLoginMenu() {
	string username, password;
	char ch;

	while (true) {
		system("cls");
		cout << "===========" << endl;
		cout << "| LOGIN MENU" << endl;
		cout << "| Press 0 to exit" << endl;
		cout << "===========" << endl;
		cout << "Username: ";
		username = "";
		getline(cin, username);

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
