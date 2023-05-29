#include "../Models/Favourites.cpp"
#include "../controllers/MemberController.cpp"
#include "../controllers/UniversityController.cpp"
// #include "../Models/Member.cpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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

    bool deleteFavoriteByID(favUniList* favData, string favoriteID) {
        favUniNode* current = favData->getHead();

        while (current != nullptr) {
            if (current->FavUniId == favoriteID) {
                favData->deleteFavNode(current); // Delete the favorite node
                cout << "Favorite university with ID " << favoriteID << " deleted." << endl;
                return true; // Return true to indicate the successful deletion
            }
            current = current->NextAddress;
        }

        cout << "Favorite university with ID " << favoriteID << " not found." << endl;
        return false; // Return false to indicate the favorite university was not found
    }
};
