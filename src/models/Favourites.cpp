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

struct TopTenUniNode {
	string UniId;
	string UniName;
	int Count = 1;

	TopTenUniNode* NextAddress;
	TopTenUniNode* PrevAddress;

} *TopTenUniHead, *TopTenUniTail, *currentTopTenUni, *newnodeTopTenUni, *SortedTopTenUniHead, *SortedTopTenUniTail;

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

	favUniList(string favoriteUni) { this->favoriteUni = favoriteUni; }
	TopTenUniNode* getSortedTopTenUniHead() { return SortedTopTenUniHead; }
	void favUniData() {
		string FavUniId, UserId, UserName, UniId, UniName, fline;
		//ifstream file("C:/Users/Acer/source/repos/assignment-dstr/Database/FavUni.csv");
		ifstream file("Database/FavUni.csv");
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
	void InsertTopTenUni(favUniNode* curr) {
		TopTenUniNode* keyNode = createNewTopTenUni(curr->UniId, curr->UniName);

		if (TopTenUniHead == NULL) {
			keyNode->PrevAddress = NULL;
			keyNode->NextAddress = NULL;
			TopTenUniHead = TopTenUniTail = keyNode;
		} else {
			keyNode->PrevAddress = TopTenUniTail;
			TopTenUniTail->NextAddress = keyNode;
			TopTenUniTail = keyNode;
			TopTenUniTail->NextAddress = NULL;
		}
	}

	void getTopTenUniData() {
		favUniNode* current = favUniHead;
		deleteTopTenUni();

		while (current != NULL) {
			filterTopTenUni(current);

			current = current->NextAddress;
		}

		// sort desc, remove all other node than first 10
		TopTenUniNode* currentTopTen = TopTenUniHead;
		while (currentTopTen != NULL) {
			sortTopTenUniByCountDesc(currentTopTen);

			currentTopTen = currentTopTen->NextAddress;
		}
		deleteAllExceptTopTen();
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
	void filterTopTenUni(favUniNode* curr) {
		TopTenUniNode* current = TopTenUniHead;
		if (current == NULL) {
			InsertTopTenUni(curr);
			return;
		} else {
			while (current != NULL) {
				if (curr->UniId == current->UniId) {
					current->Count += 1;
					return;
				}
				current = current->NextAddress;
			}

			InsertTopTenUni(curr);
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

	void deleteTopTenUni() {
		TopTenUniNode* current = TopTenUniHead;
		while (current != NULL) {
			TopTenUniNode* temp = current;
			current = current->NextAddress;
			delete temp;
		}
		TopTenUniHead = NULL;
	}

	void InsertFilterFavUni(favUniNode* curr) {
		// favUniNode* newnode = createNewFavUni(FavUniId, userID, userName, uniID, uniName);
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

	TopTenUniNode* createNewTopTenUni(string uniID, string uniName) {
		TopTenUniNode* newnode = new TopTenUniNode;
		newnode->UniId = uniID;
		newnode->UniName = uniName;
		newnode->Count = 1;
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

	void sortTopTenUniByCountDesc(TopTenUniNode* curr) {
		newnodeTopTenUni = new TopTenUniNode;

		newnodeTopTenUni->UniId = curr->UniId;
		newnodeTopTenUni->UniName = curr->UniName;
		newnodeTopTenUni->Count = curr->Count;
		newnodeTopTenUni->NextAddress = NULL;
		newnodeTopTenUni->PrevAddress = NULL;

		if (SortedTopTenUniHead == NULL) {
			SortedTopTenUniHead = SortedTopTenUniTail = newnodeTopTenUni;
		} else if (newnodeTopTenUni->Count >= SortedTopTenUniHead->Count) {
			newnodeTopTenUni->NextAddress = SortedTopTenUniHead;
			SortedTopTenUniHead->PrevAddress = newnodeTopTenUni;
			SortedTopTenUniHead = newnodeTopTenUni;
		} else if (newnodeTopTenUni->Count <= SortedTopTenUniTail->Count) {
			newnodeTopTenUni->PrevAddress = SortedTopTenUniTail;
			SortedTopTenUniTail->NextAddress = newnodeTopTenUni;
			SortedTopTenUniTail = newnodeTopTenUni;
		} else {
			currentTopTenUni = SortedTopTenUniHead->NextAddress;
			while (newnodeTopTenUni->Count <= currentTopTenUni->Count) {
				currentTopTenUni = currentTopTenUni->NextAddress;
			}
			currentTopTenUni->PrevAddress->NextAddress = newnodeTopTenUni;
			newnodeTopTenUni->PrevAddress = currentTopTenUni->PrevAddress;
			currentTopTenUni->PrevAddress = newnodeTopTenUni;
			newnodeTopTenUni->NextAddress = currentTopTenUni;
		}
	}

	void deleteAllExceptTopTen() {
		TopTenUniNode* curr = TopTenUniHead;
		int count = 0;

		while (count < 10) {
			// curr = curr->NextAddress;
			count += 1;

			if (curr->NextAddress == NULL) {
				break;
			} else {
				curr = curr->NextAddress; // test
			}
		}
		TopTenUniTail = curr;
		// TopTenUniTail->NextAddress = NULL;
		while (curr->NextAddress != NULL) {
			TopTenUniNode* temp = curr;

			curr = curr->NextAddress;
			delete temp;
		}
	}

	void overwriteFavUniData(favUniNode* saveFavUni) {
		favUniNode* current = saveFavUni;

		ofstream tempFile("temp.csv");
		//ifstream file("C:/Users/Acer/source/repos/assignment-dstr/Database/FavUni.csv");
		ifstream file("Database/FavUni.csv");
		string line;
		// bool found = false;
		tempFile << "FavUniID"
						 << ","
						 << "UserID"
						 << ","
						 << "UserName"
						 << ","
						 << "UniID"
						 << ","
						 << "UniName" << endl;
		while (current != NULL) {
			istringstream iss(line);

			tempFile << current->FavUniId << "," << current->UserId << "," << current->UserName << "," << current->UniId
							 << "," << current->UniName << endl;
			current = current->NextAddress;
		}

		file.close();
		tempFile.close();

		remove("Database/FavUni.csv");
		rename("temp.csv", "Database/FavUni.csv");
		cout << "Favourite Univerity is updated." << endl;
	}

	void addFavUniNode(favUniNode* newFavUniNode) {
		if (favUniHead == nullptr) {
			favUniHead = favUniTail = newFavUniNode;
		} else {
			favUniTail->NextAddress = newFavUniNode;
			newFavUniNode->PrevAddress = favUniTail;
			favUniTail = newFavUniNode;
		};
	}
};
