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
	string UserName;
	string UniId;
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
		favUniNode*

		favUniData();

		favUniNode* current = favUniHead;
		while (current != NULL) {
			if (userid == current->UserId) {
				InsertFilterFavUni(current);
			}
			current = current->NextAddress;
		}
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

	private:

};
