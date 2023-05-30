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
	favUniNode* favUniHead = nullptr;
	favUniNode* favUniTail = nullptr;

	public:
	favUniList(): favUniHead(nullptr), favUniTail(nullptr) {}

	favUniNode* getHead() { return favUniHead; }
	void setHead(favUniNode* head) { favUniHead = head; }

	favUniNode* getTail() { return favUniTail; }
	void setTail(favUniNode* tail) { favUniTail = tail; }

	void addFavNode(favUniNode* newNode) {
		if (favUniHead == nullptr) {
			favUniHead = favUniTail = newNode;
		} else {
			favUniTail->NextAddress = newNode;
			newNode->PrevAddress = favUniTail;
			favUniTail = newNode;
		};
	}

   void deleteFavNode(favUniNode* nodeToDelete) {
        // Handle case when the node to delete is the head node
        if (nodeToDelete == favUniHead) {
            favUniHead = nodeToDelete->NextAddress;
            if (favUniHead != nullptr) {
                favUniHead->PrevAddress = nullptr;
            } else {
                favUniTail = nullptr; // If the list becomes empty after deletion
            }
        }
        // Handle case when the node to delete is the tail node
        else if (nodeToDelete == favUniTail) {
            favUniTail = nodeToDelete->PrevAddress;
            if (favUniTail != nullptr) {
                favUniTail->NextAddress = nullptr;
            } else {
                favUniHead = nullptr; // If the list becomes empty after deletion
            }
        }
        // Handle case when the node to delete is in the middle of the list
        else {
            favUniNode* prevNode = nodeToDelete->PrevAddress;
            favUniNode* nextNode = nodeToDelete->NextAddress;

            if (prevNode != nullptr) {
                prevNode->NextAddress = nextNode;
            }
            if (nextNode != nullptr) {
                nextNode->PrevAddress = prevNode;
            }
        }

        delete nodeToDelete; // Delete the node from memory
    }

	void displayAll() {
		favUniNode* current = favUniHead;
		// Print table header
		printTableRow("FavUniID", "UniID", "UniName");
		while (current != nullptr) {
			// Print information for each node
			printTableRow(current->FavUniId, current->UniId, current->UniName);
			current = current->NextAddress; // Move to the next node
		}
	}

	private:
	void printTableRow(const string& col1, const string& col2, const string& col3) {
		int col1Width = 15;
		int col2Width = 30;
		int col3Width = 30;

		cout << left << setw(col1Width) << col1.substr(0, col1Width) << " | "
			 << setw(col2Width) << col2.substr(0, col2Width) << " | "
			 << setw(col3Width) << col3.substr(0, col3Width) << " | " << endl;

		cout << setfill('-') << setw(col1Width + col2Width + col3Width + 15) << "" << setfill(' ')<< endl;
	}
};
