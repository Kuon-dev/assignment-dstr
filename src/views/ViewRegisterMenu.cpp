#include <conio.h>
#include <iostream>
#include <string>
#include "UserDashboard.cpp"
#include "../Modules/InputHandler.cpp"

using namespace std;

bool authenticateUser(string username, string password) {
	// hard-coded credentials for now
	return (username == "admin" && password == "password");

}

void displayRegisterMenu() {
	string name = handleStringInput("Input your name");
	string username = handleStringInput("Input your name");

	// after input sanized
}
