#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <iomanip>
#include <typeinfo>

using namespace std;

struct favUniNode {
	string FavUniId;
	string UserId;
	string UniId;
	string UserName;
	string UniName;

	favUniNode* NextAddress;
	favUniNode* PrevAddress;

} *favUniHead, *favUniTail, *currentFavUni, *newnodeFavUni, *filterUserFavUniHead, *filterUserFavUniTail;


class favUniList {
	favUniNode* favUniHead = NULL;
	favUniNode* favUniTail = NULL;
	favUniNode* filterUserFavUniHead = NULL;
	favUniNode* filterUserFavUniTail = NULL;
	string favoriteUni;

	public:

		favUniList(): favUniHead(nullptr), favUniTail(nullptr) {}

	favUniNode* getHead() { return favUniHead; }
	void setHead(favUniNode* head) { favUniHead = head; }

	favUniNode* getTail() { return favUniTail; }
	void setTail(favUniNode* tail) { favUniTail = tail; }
	favUniNode* getFilteredHead() { return filterUserFavUniHead; }

	favUniList(string favoriteUni) {
		this->favoriteUni = favoriteUni;
	}

	void favUniData() {

		string FavUniId, UserId, UserName, UniId, UniName, fline;

		ifstream file("C:\\Users\\Acer\\source\\repos\\assignment-dstr\\Database\\FavUni.csv");
		getline(file, fline);
		while (file.good()) {
			newnodeFavUni = new favUniNode;

			getline(file, FavUniId, ',');
			getline(file, UserId, ',');
			getline(file, UserName, ',');
			getline(file, UniId, ',');
			getline(file, UniName);

			if (FavUniId == "") {
				break;
			} else if (FavUniId == "FavUniId") {
				continue;
			}

			InsertFavUni(FavUniId, UserId, UserName, UniId, UniName);
		}
	}

	void filterFavUniData(string userid) {
		deleteFilteredFUL();
		favUniNode* current = favUniHead;

		while (current != NULL) {
			if (userid == current->UserId) {
				InsertFilterFavUni(current);
			}
			current = current->NextAddress;
		}
	}

	void deleteFilteredFUL() {
		favUniNode* current = filterUserFavUniHead;
		while (current != NULL) {
			favUniNode* temp = current;
			current = current->NextAddress;
			delete temp;
		}
		filterUserFavUniHead = NULL;
	}

	void InsertFilterFavUni(favUniNode* curr) {
		//favUniNode* newnode = createNewFavUni(FavUniId, userID, userName, uniID, uniName);
		favUniNode* keyNode = createNewFavUni(curr->FavUniId, curr->UserId, curr->UserName, curr->UniId, curr->UniName);
			
		
		if (filterUserFavUniHead == NULL) {
			
			keyNode->PrevAddress == NULL;
			keyNode->NextAddress == NULL;
			filterUserFavUniHead = filterUserFavUniTail = keyNode;
		} else {
			keyNode->PrevAddress = filterUserFavUniTail;
			filterUserFavUniTail->NextAddress = keyNode;
			filterUserFavUniTail = keyNode;
		}

	}

	favUniNode* createNewFavUni(string FavUniId, string userID, string userName, string uniID, string uniName) {
		favUniNode* newnode = new favUniNode;
		newnode->FavUniId = FavUniId;
		newnode->UserId = userID;
		newnode->UserName = userName;
		newnode->UniId = uniID;
		newnode->UniName = uniName;
		newnode->NextAddress = NULL;
		newnode->PrevAddress = NULL;

		return newnode;
	}

	void InsertFavUni(string FavUniId, string userID, string userName, string uniID, string uniName) {
		favUniNode* newnode = createNewFavUni(FavUniId, userID, userName, uniID, uniName);
		if (favUniHead == NULL) {
			favUniHead = favUniTail = newnode;
		} else {
			newnode->PrevAddress = favUniTail;
			favUniTail->NextAddress = newnode;
			favUniTail = newnode;
		}
	}

	void overwriteFavUniData(favUniNode* saveFavUni) {
		favUniNode* current = saveFavUni;
		
		ofstream tempFile("temp.csv");
		ifstream file("C:\\Users\\Acer\\source\\repos\\assignment-dstr\\Database\\FavUni.csv");
		string line;
		//bool found = false;
		tempFile << "FavUniID" << "," << "UserID" << "," << "UserName" << "," << "UniID" << "," << "UniName" << endl;
		while (current!=NULL) {
			
			istringstream iss(line);
			//string FavUniId, UserID, UserName, UniID, UniName;
			////newnodeFavUni = new favUniNode;
			//cout << "test2" << endl;
			//getline(file, FavUniId, ',');
			//getline(file, UserID, ',');
			//getline(file, UserName, ',');
			//getline(file, UniID, ',');
			//getline(file, UniName);
			
			tempFile << current->FavUniId << "," << current->UserId << "," << current->UserName << "," << current->UniId
							 << "," << current->UniName << endl;
			current=current->NextAddress;

		}
		file.close();
		tempFile.close();
		//if (found) {
			remove("C:\\Users\\Acer\\source\\repos\\assignment-dstr\\Database\\FavUni.csv");
			rename("temp.csv", "C:\\Users\\Acer\\source\\repos\\assignment-dstr\\Database\\FavUni.csv");
			cout << "Favourite Univerity is updated." << endl;
		/*} else {
			remove("temp.csv");
			cout << "Favourite Univerity is not updated." << endl;
		}*/

	}

	

};
