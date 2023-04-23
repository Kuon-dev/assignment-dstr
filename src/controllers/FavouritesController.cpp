#include "../Models/Favourites.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FavouritesController {
	public:
	void displayFavUni() {
		favUniNode* current = favUniHead;
		while (current != NULL) {
			cout << "Favourite University ID: " << current->FavUniId << endl;
			cout << "Account ID: " << current->UserId << endl;
			cout << "Account Username: " << current->UserName << endl;
			cout << "University ID: " << current->UniId << endl;
			cout << "University Name: " << current->UniName << endl;
			cout << endl;
			current = current->NextAddress;
		}
		cout << "list ended at here." << endl;
	}

	void add_newnode_to_end_of_list_history() {
		// newnodeHist = new history_List;
		newnodeFavUni->NextAddress = NULL;
		newnodeFavUni->PrevAddress = NULL;
		// situation 1: list empty
		if (favUniHead == NULL) {
			favUniHead = favUniTail = newnodeFavUni; // changes for doubly
		}
		// situation 2: list not empty
		else {
			newnodeFavUni->PrevAddress = favUniTail;
			favUniTail->NextAddress = newnodeFavUni;
			favUniTail = newnodeFavUni;
		}
	}


	void displayFavUniName() {
		favUniNode* current = favUniHead;
		while (current != NULL) {
			cout << "University Name: " << current->UniName << endl;
			cout << endl;
			current = current->NextAddress;
		}
	}

	void count() // function to count number of nodes
	{
		struct favUniNode* current = favUniHead;

		// bool exe = false;

		// Iterating till end of list
		for (int cnt = 1; current != NULL; cnt++) {
			current = current->NextAddress;

			if (current == NULL) {
				// exe = true;
				cout << cnt << endl;
			}
		};
	}

	void deleteBasedOnFavUni() {
		string favUniListID = "";
		while (favUniListID == "") {
			cout << "Please enter the ID for record in Favourite University List to be deleted: " << endl;
			getline(cin, favUniListID);
			cout << endl;
		}

		{
			if (favUniHead == NULL) {
				cout << endl;
				cout << endl;
				cout << "The List of Favorite University is empty." << endl;
				cout << "No records will be deleted." << endl;
				cout << endl;
				return;
			}
			if (favUniHead->FavUniId == favUniListID) // delete from the front list
			{
				favUniNode* currentFavUni = favUniHead;
				favUniHead = favUniHead->NextAddress;
				cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
				cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
				delete currentFavUni;
			} else {
				favUniNode* PrevAddress = favUniHead;
				favUniNode* currentFavUni = favUniHead->NextAddress;

				while (currentFavUni != NULL) {
					if (currentFavUni->FavUniId == favUniListID) {
						PrevAddress->NextAddress = currentFavUni->NextAddress;
						cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
						cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
						delete currentFavUni;
						return;
					}
					PrevAddress = currentFavUni;
					currentFavUni = currentFavUni->NextAddress;
				}
				cout << "Record of Favorite University in List with ID of " << favUniListID << " is not found." << endl;
			}
		}
	}
};