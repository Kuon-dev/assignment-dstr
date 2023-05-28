#include "../Models/Favourites.cpp"
#include "../controllers/UniversityController.cpp"
#include "../controllers/MemberController.cpp"
// #include "../Models/Member.cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FavouritesController {
	private:
	favUniList favouriteList;

	public:
	favUniList* readFavUniDatabase() {
		favUniList* list = new favUniList();
		ifstream file("Database/FavUni.csv"); // get user database
		// validate file open
		if (!file.is_open()) {
			cout << "\033[31m"
				<< "Error: could not open file "
				<< "\033[0m" << endl;
			return list;
		}
		// define database header and line
		string header, line;
		getline(file, header); // Read and ignore the header line

		while (getline(file, line)) {
			stringstream iss(line);
			favUniNode* node = new favUniNode();
			string FavUniId, UserId, UniId, UserName, UniName;

			getline(iss, FavUniId, ',');
			getline(iss, UserId, ',');
			getline(iss, UserName, ',');
			getline(iss, UniId, ',');
			getline(iss, UniName, ',');

			node->FavUniId = FavUniId;
			node->UserId = UserId;
			node->UserName = UserName;
			node->UniId = UniId;
			node->UniName = UniName;

			list->addFavUniNode(node);
		}

		file.close();
		return list;
	}

	favUniList* getUserFav(favUniList* data, userNode* user){
		favUniList* favUni = new favUniList;
		favUniNode* current = data->getHead();
		while (current != nullptr) {
			if (current->UserId == user->UserId) favUni->addFavUniNode(current);
			current = current->NextAddress;
		}
		return favUni;
	}

	void displayFavUni(favUniNode* head) {
		favUniNode* current = head;

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

	void displayTopTenUniData() {
		favouriteList.getTopTenUniData();
		TopTenUniNode* current = favouriteList.getSortedTopTenUniHead();
		cout << endl;

		// favouriteList.overwriteFavUniData();
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "Top 10 university added as favourite university by members:" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;

		cout << endl;
		while (current != NULL) {
			cout << "University ID: " << current->UniId << endl;
			cout << "University Name: " << current->UniName << endl;
			cout << "Total: " << current->Count << endl;
			cout << endl;
			current = current->NextAddress;
		}
		cout << "Report ends at here." << endl;
	}

	void addNodeToEnd() {
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

	void count() // function to count number of nodes
	{
		struct favUniNode* current = favUniHead;

		// Iterating till end of list
		for (int cnt = 1; current != NULL; cnt++) {
			current = current->NextAddress;

			if (current == NULL) {
				cout << cnt << endl;
			}
		};
	}

	favUniNode* searchFavUniWithID(string favlistid, favUniNode* filteredhead) {
		favUniNode* current = filteredhead;
		while (current != NULL) {
			if (favlistid == current->FavUniId) {
				return current;
			}

			current = current->NextAddress;
		}
		cout << "No record found." << endl;
		return NULL;
	}

	void deleteBasedOnFavUni(string favlistid) {
		favUniNode* searchNode = searchFavUniWithID(favlistid, favouriteList.getFilteredHead());

		favUniNode* unfilteredHead = favouriteList.getHead();
		if (unfilteredHead == NULL) {
			cout << endl;
			cout << endl;
			cout << "The List of Favorite University is empty." << endl;
			cout << "No records will be deleted." << endl;
			cout << endl;
			return;
		}

		if (searchNode == NULL) {
			return;
		}

		if (searchNode->FavUniId == unfilteredHead->FavUniId) // delete from the front list
		{
			favUniNode* currentFavUni = unfilteredHead;
			favouriteList.setHead(unfilteredHead->NextAddress);
			if (favouriteList.getHead() != NULL) {
				favouriteList.getHead()->PrevAddress = NULL;
			} else {
				favouriteList.setTail(NULL);
			}
			cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
			cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
			delete currentFavUni;
			favouriteList.overwriteFavUniData(getHead());

		} else if (searchNode->FavUniId == favouriteList.getTail()->FavUniId) {
			favUniNode* currentFavUni = favouriteList.getTail();
			favouriteList.setTail(favouriteList.getTail()->PrevAddress);

			if (favouriteList.getTail() != NULL) {
				favouriteList.getTail()->NextAddress = NULL;

			} else {
				favouriteList.setHead(NULL);
			}
			cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
			cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
			delete currentFavUni;
			favouriteList.overwriteFavUniData(getHead());
		} else {
			favUniNode* PrevAddress = unfilteredHead;
			favUniNode* currentFavUni = unfilteredHead->NextAddress;

			while (currentFavUni != NULL) {
				if (currentFavUni->FavUniId == searchNode->FavUniId) {
					PrevAddress->NextAddress = currentFavUni->NextAddress;
					cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
					cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
					delete currentFavUni;
					favouriteList.overwriteFavUniData(getHead());
					return;
				}
				PrevAddress = currentFavUni;
				currentFavUni = currentFavUni->NextAddress;
			}
			cout << "Record of Favorite University record in List with ID of " << searchNode->FavUniId << " is not found."
					 << endl;
		}
	}

	void createUserFavUni(string input, string testname, string testmemberid) {
		UniversityContoller uniObject;
		universityList uniCurrentList = uniObject.readUniversityDatabaseLinkedList();
		universitySearcher searcher;
		universityNode* searched = searcher.binarySearch(uniCurrentList.getHead(), "Rank", stoi(input));

		string ID, Name;
		ID = testmemberid;
		Name = testname;
		favUniHead = currentFavUni = favUniTail = NULL;

		favouriteList.InsertFavUni(
			to_string(stoi(favouriteList.getTail()->FavUniId) + 1), ID, Name, to_string(searched->Rank), searched->Name);
		favouriteList.overwriteFavUniData(getHead());
	}

	favUniNode* getHead() { return favouriteList.getHead(); }

	favUniNode* getFilteredHead() { return favouriteList.getFilteredHead(); }
};
