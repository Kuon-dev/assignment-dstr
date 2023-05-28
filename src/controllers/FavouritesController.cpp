#include "../Models/Favourites.cpp"
#include "../controllers/UniversityController.cpp"
// #include "../Models/Member.cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FavouritesController {
	private:
	favUniList favouritesobj;

	public:

		favUniList* readFavUniDatabase() {
		favUniList* list = new favUniList();
		//ifstream file("C:/Users/Acer/source/repos/Kuon-dev/assignment-dstr/Database/FavUni.csv"); // get user database
		ifstream file("Database/FavUni.csv");
		// validate file open
		if (!file.is_open()) {
			cout << "\033[31m"
					 << "Error: could not open file "
					 << "\033[0m" << endl;
			return list;
		}
		// define database haeder and line
		string header, line;
		getline(file, header);
		while (getline(file, line)) {
			stringstream iss(line);
			favUniNode* node = new favUniNode();
			string FavUniId;
			string UserId;
			string UniId;
			string UserName;
			string UniName;
			string token; // to get value
			getline(iss, token, ',');
			FavUniId = token;
			getline(iss, token, ',');
			UserId = token;
			getline(iss, token, ',');
			UserName = token;
			getline(iss, token, ',');
			UniId = token;
			getline(iss, token, ',');
			UniName = token;
			node->FavUniId = FavUniId;
			node->UserId = UserId;
			node->UserName = UserName;
			node->UserName = UserName;
			node->UniId = UniId;
			node->UniName = UniName;
			list->addFavUniNode(node);
		};
		file.close();
		return list;
	};

	favUniNode* readFavDatabase(string UserId) {
		// read from csv
		favouritesobj.deleteFilteredFUL();
		// append to userFavList if user id is equal
		favouritesobj.filterFavUniData(UserId);

		favUniNode* userFavList = favouritesobj.getFilteredHead();

		// retrun fav list
		return userFavList;
	}
	void getFULinkListFromDB() {
		favouritesobj.deleteFUL();
		favouritesobj.favUniData();
	}

	void displayFavUni(favUniNode* head) {
		favUniNode* current = head;
		// favouritesobj.overwriteFavUniData();
		cout << endl;
		cout << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << "List of University saved as Favourite" << endl;

		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << endl;
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
		cout << endl;
		cout << endl;
	}

	void displayTopTenUniData() {
		favouritesobj.getTopTenUniData();
		TopTenUniNode* current = favouritesobj.getSortedTopTenUniHead();
		cout << endl;

		// favouritesobj.overwriteFavUniData();
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
		favUniNode* searchNode = searchFavUniWithID(favlistid, favouritesobj.getFilteredHead());

		favUniNode* unfilteredHead = favouritesobj.getHead();
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
			favouritesobj.setHead(unfilteredHead->NextAddress);
			if (favouritesobj.getHead() != NULL) {
				favouritesobj.getHead()->PrevAddress = NULL;
			} else {
				favouritesobj.setTail(NULL);
			}
			cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
			cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
			delete currentFavUni;
			favouritesobj.overwriteFavUniData(getHead());

		} else if (searchNode->FavUniId == favouritesobj.getTail()->FavUniId) {
			favUniNode* currentFavUni = favouritesobj.getTail();
			favouritesobj.setTail(favouritesobj.getTail()->PrevAddress);

			if (favouritesobj.getTail() != NULL) {
				favouritesobj.getTail()->NextAddress = NULL;

			} else {
				favouritesobj.setHead(NULL);
			}
			cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
			cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
			delete currentFavUni;
			favouritesobj.overwriteFavUniData(getHead());
		} else {
			favUniNode* PrevAddress = unfilteredHead;
			favUniNode* currentFavUni = unfilteredHead->NextAddress;

			while (currentFavUni != NULL) {
				if (currentFavUni->FavUniId == searchNode->FavUniId) {
					PrevAddress->NextAddress = currentFavUni->NextAddress;
					cout << "Deleted: University with ID of " << currentFavUni->UniId << endl;
					cout << "Deleted: University with Name of " << currentFavUni->UniName << endl;
					delete currentFavUni;
					favouritesobj.overwriteFavUniData(getHead());
					return;
				}
				PrevAddress = currentFavUni;
				currentFavUni = currentFavUni->NextAddress;
			}
			cout << "Record of Favorite University record in List with ID of " << searchNode->FavUniId << " is not found."
					 << endl;
		}
	}

	void createUserFavUni(string input, string testmemberid, string testname) {
		UniversityContoller uniObject;

		universityList uniCurrentList = uniObject.readUniversityDatabaseLinkedList();

		universitySearcher searcher;

		universityNode* searched = searcher.binarySearch(uniCurrentList.getHead(), "Rank", stoi(input));

		string ID, Name;
		/*cout << "enter user id as temporary member id for fav uni" << endl;
		cin >> ID;
		cout << "enter user name as temporary member name for fav uni" << endl;
		cin >> Name;*/

		ID = testmemberid;
		Name = testname;
		favUniHead = currentFavUni = favUniTail = NULL;

		favouritesobj.InsertFavUni(
			to_string(stoi(favouritesobj.getTail()->FavUniId) + 1),
			testmemberid,
			testname,
			to_string(searched->Rank),
			searched->Name);
		favouritesobj.overwriteFavUniData(getHead());
	}


	favUniNode* getHead() { return favouritesobj.getHead(); }

	favUniNode* getFilteredHead() { return favouritesobj.getFilteredHead(); }
};
