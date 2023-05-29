#include "../Models/Favourites.cpp"
#include "../controllers/MemberController.cpp"
#include "../controllers/UniversityController.cpp"
// #include "../Models/Member.cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

 struct UniFavCountNode {
        string UniId;
        int favCount;
        UniFavCountNode* next;
};

class FavouritesController {
	private:
	favUniList favouriteList;
	favUniNode* getHead() { return favouriteList.getHead(); }
	int createFeedbackId(favUniList* data) {
		favUniNode * lastNode = data->getTail();
		if (lastNode == nullptr) return 1;
		else if (lastNode->FavUniId== "") return 1;
		else return (stoi(lastNode->FavUniId) + 1);
	}
    favUniNode* binarySearchByID(favUniNode* startNode, favUniNode* endNode, const std::string& targetID) {
        if (startNode == nullptr || endNode == nullptr) {
            return nullptr;
        }

        favUniNode* midNode = getMiddleNode(startNode, endNode);
        if (midNode->FavUniId == targetID) {
            return midNode;
        } else if (midNode->FavUniId > targetID) {
            return binarySearchByID(startNode, midNode->PrevAddress, targetID);
        } else {
            return binarySearchByID(midNode->NextAddress, endNode, targetID);
        }
    }

    favUniNode* getMiddleNode(favUniNode* startNode, favUniNode* endNode) {
        if (startNode == nullptr || endNode == nullptr) {
            return nullptr;
        }

        favUniNode* slowPtr = startNode;
        favUniNode* fastPtr = startNode->NextAddress;

        while (fastPtr != endNode) {
            fastPtr = fastPtr->NextAddress;
            if (fastPtr != endNode) {
                slowPtr = slowPtr->NextAddress;
                fastPtr = fastPtr->NextAddress;
            }
        }

        return slowPtr;
    }
	int getLength(universityList* list) {
		int length = 0;
		universityNode* current = list->getHead();

		while (current != nullptr) {
			length++;
			current = current->next;
		}

		return length;
	}

	public:
	favUniList* readFavUniDatabase() {
		favUniList* list = new favUniList();
		ifstream file("Database/Favourites.csv"); // get user database
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

			list->addFavNode(node);
		}

		file.close();
		return list;
	}

	void writeToDatabase(favUniList* favData) {
		favUniNode* current = favData->getHead();
		ofstream tempFile("temp.csv");
		ifstream file("Database/Favourites.csv");
		string line;
		tempFile << "FavUniID,UserID,UserName,UniID,UniName" << endl;
		while (current != NULL) {
			istringstream iss(line);

			tempFile << current->FavUniId << "," << current->UserId << "," << current->UserName << "," << current->UniId
							 << "," << current->UniName << endl;
			current = current->NextAddress;
		}

		file.close();
		tempFile.close();

		remove("Database/Favourites.csv");
		rename("temp.csv", "Database/Favourites.csv");
		cout << "Favourite Univerity is updated." << endl;
	}

	favUniList* getFavouritesByUser(favUniList* data, userNode* user) {
		favUniList* favUni = new favUniList;
		favUniNode* current = data->getHead();
		while (current != nullptr) {
			if (current->UserId == user->UserId) favUni->addFavNode(current);
			current = current->NextAddress;
		}
		return favUni;
	}

    universityNode* searchUniversityByRank(universityList* uniData, int rank) {
        universityNode* current = uniData->getHead();

        while (current != nullptr) {
            if (current->Rank == rank) {
                return current; // Found the university with the specified ID
            }
            current = current->next;
        }
        return nullptr; // University with the specified ID not found
    }

    bool addFavorite(universityList* uniData, favUniList* favData, userNode* currentUser, int rank) {
        // Check if the university already exists in the uniData
        universityNode* university = searchUniversityByRank(uniData, rank);
        if (university == nullptr) {
            cout << "University with Rank " << rank << " does not exist." << endl;
            return false; // Return false to indicate that the addition was unsuccessful
        }
		favUniNode* newNode = new favUniNode;
		newNode->FavUniId = to_string(createFeedbackId(favData));
		newNode->UniId = to_string(university->Rank);
		newNode->UniName = university->Name;
		newNode->UserName = currentUser->userUserName;
		newNode->UserId = currentUser->UserId;
		favData->addFavNode(newNode);
        // Your logic for adding the university as a favorite goes here

        cout << "University " << university->Name << " added as a favorite." << endl;
        return true; // Return true to indicate that the addition was successful
    }

    bool deleteFavoriteByID(favUniList* favData, userNode* currentUser, string favoriteID) {
        favUniNode* current = favData->getHead();

        while (current != nullptr) {
            if (current->FavUniId == favoriteID) {
				if (current->UserId != currentUser->UserId) return false;
                favData->deleteFavNode(current); // Delete the favorite node
                cout << "Favorite university with ID " << favoriteID << " deleted." << endl;
                return true; // Return true to indicate the successful deletion
            }
            current = current->NextAddress;
        }

        cout << "Favorite university with ID " << favoriteID << " not found." << endl;
        return false; // Return false to indicate the favorite university was not found
    }

    favUniNode* searchFavoriteByID(favUniList* favData, string favoriteID) {
        return binarySearchByID(favData->getHead(), favData->getTail(), favoriteID);
    }

    // Function to find and increment the favCount for a university
    UniFavCountNode* findAndIncrementFavCount(UniFavCountNode* head, string UniId) {
        UniFavCountNode* node = head;
        while (node != nullptr) {
            if (node->UniId == UniId) {
                node->favCount++;
                return head;
            }
            node = node->next;
        }
        // University not found, add new node
        UniFavCountNode* newNode = new UniFavCountNode;
        newNode->UniId = UniId;
        newNode->favCount = 1;
        newNode->next = head;
        return newNode;
    }

	universityNode* getUniversityById(universityList& uList, int Rank) {
		universityNode* current = uList.getHead();
		while (current != nullptr) {
			if (current->Rank == Rank) {
				cout << current->Name;
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

    // Function to return the top 10 universities
    universityList* getTopFavouritedUniversities(universityList* uniData, favUniNode* head) {
        // Generate frequency counts
        UniFavCountNode* favCounts = nullptr;
        for (favUniNode* node = head; node != nullptr; node = node->NextAddress) {
            favCounts = findAndIncrementFavCount(favCounts, node->UniId);
        }

        // Convert favCounts to universityList for sorting
        universityList countsList;
        for (UniFavCountNode* node = favCounts; node != nullptr; node = node->next) {
            universityNode* newNode = new universityNode;
            newNode->Name = node->UniId;
            newNode->Rank = node->favCount;
            countsList.addUniversityNode(newNode);
        }

        // Sort countsList by favCount in descending order
        newMergeSort sorter;
        sorter.mergeSortInt(countsList, "Rank", "dsc");

        // Extract top 10 universities
		universityList uniDataCopy = *uniData;
		universityList* topFavourites = new universityList();
		int range = getLength(&countsList);

		universityNode* uniNode = countsList.getHead();
		for (int i = 0; i < ((range <= 10) ? range : 10) && uniNode != nullptr; i++, uniNode = uniNode->next) {
			universityNode* actualUniNode = getUniversityById(uniDataCopy, stoi(uniNode->Name));
			universityNode* copyNode = new universityNode;
			*copyNode = *actualUniNode;
			copyNode->prev = nullptr;
			copyNode->next = nullptr;
			topFavourites->addUniversityNode(copyNode);
		}
		// Cleanup
        while (favCounts != nullptr) {
            UniFavCountNode* next = favCounts->next;
            delete favCounts;
            favCounts = next;
        }

		cout << "Done clean up" << endl;

        return topFavourites;
    }
};
