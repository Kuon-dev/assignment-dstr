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

} *favUniHead, *favUniTail, *currentFavUni, *newnodeFavUni;


class favUniList {
	favUniNode* favUniHead = NULL;
	favUniNode* favUniTail = NULL;
	string favoriteUni;

	public:
	favUniList(string favoriteUni) { this->favoriteUni = favoriteUni; }

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
};
