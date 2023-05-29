#include "../Models/University.cpp"
#include <cctype>
#include <string>

using namespace std;
/*
---------------------------------
| Helper function section
---------------------------------
| This section contains list of helper functions
|
*/
double stringToDouble(string s) {
	if (s.empty()) return 0.0;

	try {
		// convert string to double with decimal point
		return stod(s);
	} catch (const std::invalid_argument& e) {
		// handle invalid input string
		return 0.0;
	}
}

string toLower(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = std::tolower(s[i]);
	}
	size_t firstNonSpace = s.find_first_not_of(' ');

	if (firstNonSpace != std::string::npos) {
		return s.erase(0, firstNonSpace);
	}
	return s;
}

// for uni
string getColumn(universityNode* node, string column) {
    if (column == "Rank") return to_string(node->Rank);
    else if (column == "Name") return node->Name;
    else if (column == "LocationCode") return node->LocationCode;
    else if (column == "Location") return node->Location;
    else if (column == "ArScore") return node->ArScore;
    else if (column == "ArRank") return node->ArRank;
    else if (column == "ErScore") return node->ErScore;
    else if (column == "ErRank") return node->ErRank;
    else if (column == "FsrScore") return node->FsrScore;
    else if (column == "FsrRank") return node->FsrRank;
    else if (column == "CpfScore") return node->CpfScore;
    else if (column == "CpfRank") return node->CpfRank;
    else if (column == "IfrScore") return node->IfrScore;
    else if (column == "IfrRank") return node->IfrRank;
    else if (column == "IsrScore") return node->IsrScore;
    else if (column == "IsrRank") return node->IsrRank;
    else if (column == "IrnScore") return node->IrnScore;
    else if (column == "IrnRank") return node->IrnRank;
    else if (column == "GerScore") return node->GerScore;
    else if (column == "GerRank") return node->GerRank;
    else if (column == "ScoreScaled") return node->ScoreScaled;
    else return "";
}
/*
---------------------------------
|  sort algorithm for uni
--------------------------------
| This class will contain quick and merge sort
| algorithms for universities dataset
|
| Helper functions will be placed under private section of the code
|
*/


class newMergeSort {
public:

	universityNode* SortedMerge(universityNode* a, universityNode* b, string column)
	{
		universityNode* result = nullptr;

		if (a == nullptr)
			return (b);
		else if (b == nullptr)
			return (a);

		// Sorting by name in ascending order.
		if (getColumn(a, column) <= getColumn(b, column)) {
			result = a;
			result->next = SortedMerge(a->next, b, column);
			result->next->prev = result;
			result->prev = nullptr;
		}
		// If names are same then sort by rank in descending order.
		else {
        result = b;
			result->next = SortedMerge(a, b->next, column);
			result->next->prev = result;
			result->prev = nullptr;
		}
		return (result);
	}

	universityNode* Split(universityNode* head)
	{
		universityNode* fast = head, *slow = head;
		while (fast->next && fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		universityNode* temp = slow->next;
		slow->next = nullptr;
		return temp;
	}

	universityNode* MergeSort(universityNode* head, string column)
	{
		if (!head || !head->next)
			return head;
		universityNode* second = Split(head);

		// Recur for left and right halves.
		head = MergeSort(head, column);
		second = MergeSort(second, column);

		// Merge the two sorted halves.
		return SortedMerge(head, second, column);
	}

	void mergeSortString(universityList& uList, string column) {
		universityNode* newHead = MergeSort(uList.getHead(), column);
		uList.setHead(newHead);

		// Reset tail of the list.
		universityNode* newTail = newHead;
		while(newTail && newTail->next) {
			newTail = newTail->next;
		}
		uList.setTail(newTail);
	}

    // SortedMerge function specialized for integers.
    universityNode* SortedMergeInt(universityNode* a, universityNode* b, string column, string order) {
        universityNode* result = nullptr;

        if (a == nullptr)
            return b;
        else if (b == nullptr)
            return a;

        // Sorting by column in ascending order.
        if (order == "asc") {
            if (stoi(getColumn(a, column)) <= stoi(getColumn(b, column))) {
                result = a;
                result->next = SortedMergeInt(a->next, b, column, order);
            } else {
                result = b;
                result->next = SortedMergeInt(a, b->next, column, order);
            }
        }
        // Sorting by column in descending order.
        else if (order == "dsc") {
            if (stoi(getColumn(a, column)) >= stoi(getColumn(b, column))) {
                result = a;
                result->next = SortedMergeInt(a->next, b, column, order);
            } else {
                result = b;
                result->next = SortedMergeInt(a, b->next, column, order);
            }
        }

        if (result->next)
            result->next->prev = result;

        return result;
    }

    // MergeSort function specialized for integers.
    universityNode* MergeSortInt(universityNode* head, string column, string order) {
        if (!head || !head->next)
            return head;
        universityNode* second = Split(head);

        // Recur for left and right halves.
        head = MergeSortInt(head, column, order);
        second = MergeSortInt(second, column, order);

        // Merge the two sorted halves.
        return SortedMergeInt(head, second, column, order);
    }

    void mergeSortInt(universityList& uList, string column, string order) {
        universityNode* newHead = MergeSortInt(uList.getHead(), column, order);
        uList.setHead(newHead);

        // Reset tail of the list.
        universityNode* newTail = newHead;
        while (newTail && newTail->next) {
            newTail = newTail->next;
        }
        uList.setTail(newTail);
    }
};


class newQuickSort {
	public:
	universityNode* quicksortString(universityNode* head, universityNode* tail, string column) {
		if (head == nullptr || head == tail) {
			return head;
		}

		universityNode* pivot = partitionString(head, tail, column);

		// get new tail for the left partition
		universityNode* newTail = pivot != nullptr ? pivot->prev : getTail(head);

		if (newTail != nullptr)
			newTail->next = nullptr;  // make it tail

		head = quicksortString(head, newTail, column);

		if (newTail != nullptr && head != nullptr) {
			// find tail again after sorting
			newTail = getTail(head);
			// connect pivot to the sorted list
			newTail->next = pivot;
		}

		pivot->next = quicksortString(pivot->next, tail, column);

		return head;
	}

    universityNode* quicksortInt(universityNode* head, universityNode* tail, string column) {
   		if (head == nullptr || head == tail) {
			return head;
		}

		universityNode* pivot = partitionInt(head, tail, column);

		// get new tail for the left partition
		universityNode* newTail = pivot != nullptr ? pivot->prev : getTail(head);

		if (newTail != nullptr)
			newTail->next = nullptr;  // make it tail

		head = quicksortInt(head, newTail, column);

		if (newTail != nullptr && head != nullptr) {
			// find tail again after sorting
			newTail = getTail(head);
			// connect pivot to the sorted list
			newTail->next = pivot;
		}

		pivot->next = quicksortInt(pivot->next, tail, column);

		return head;
	}

	private:
    universityNode* partitionString(universityNode* head, universityNode* tail, string column) {
        string pivot = getColumn(tail, column);

        universityNode* i = head->prev;

        for (universityNode* j = head; j != tail; j = j->next) {
            if (getColumn(j, column) <= pivot) {
                i = (i == nullptr) ? head : i->next;
                swapNodes(i, j);
            }
        }

        i = (i == nullptr) ? head : i->next;
        swapNodes(i, tail);

        return i;
    }

    universityNode* partitionInt(universityNode* head, universityNode* tail, string column) {
        int pivot = stoi(getColumn(tail, column));

        universityNode* i = head->prev;

        for (universityNode* j = head; j != tail; j = j->next) {
            if (stoi(getColumn(j, column)) <= pivot) {
                i = (i == nullptr) ? head : i->next;
                swapNodes(i, j);
            }
        }

        i = (i == nullptr) ? head : i->next;
        swapNodes(i, tail);

        return i;
    }

    void swapNodes(universityNode* node1, universityNode* node2) {
        if (node1 != node2) {
            swap(node1->Rank, node2->Rank);
            swap(node1->Name, node2->Name);
            swap(node1->LocationCode, node2->LocationCode);
            swap(node1->Location, node2->Location);
            swap(node1->ArScore, node2->ArScore);
            swap(node1->ArRank, node2->ArRank);
            swap(node1->ErScore, node2->ErScore);
            swap(node1->ErRank, node2->ErRank);
            swap(node1->FsrScore, node2->FsrScore);
            swap(node1->FsrRank, node2->FsrRank);
            swap(node1->CpfScore, node2->CpfScore);
            swap(node1->CpfRank, node2->CpfRank);
            swap(node1->IfrScore, node2->IfrScore);
            swap(node1->IfrRank, node2->IfrRank);
            swap(node1->IsrScore, node2->IsrScore);
            swap(node1->IsrRank, node2->IsrRank);
            swap(node1->IrnScore, node2->IrnScore);
            swap(node1->IrnRank, node2->IrnRank);
            swap(node1->GerScore, node2->GerScore);
            swap(node1->GerRank, node2->GerRank);
            swap(node1->ScoreScaled, node2->ScoreScaled);
        }
    }

    universityNode* getTail(universityNode* node) {
        while (node != nullptr && node->next != nullptr) {
            node = node->next;
        }
        return node;
    }
};
/*
---------------------------------
| Searchers
---------------------------------
| This section contains binary search algorithm for
| university node
|
*/

class universitySearcher {
	public:
	universityNode* binarySearch(universityNode* head, string column, int name) {
		int low = 1, high = 0;
		for (universityNode* p = head; p != nullptr; p = p->next) {
			high++;
		}
		while (low <= high) {
			int mid = (low + high) / 2;
			universityNode* p = head;
			for (int i = 1; i < mid; i++) {
				p = p->next;
			}
			if (stoi(getColumn(p, column)) == name) {
				return p;
			} else if (stoi(getColumn(p, column)) < name) {
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}

		return nullptr;
	};

	universityList linearSearch(universityNode* head, string column, string query) {
		universityList newList;
		universityNode* current = head;
		universityNode* currentNext = nullptr;
		universityNode* matched = nullptr;

		while (current != nullptr) {
			currentNext = current->next; // Assign next node before moving current

			if (fuzzyMatch(getColumn(current, column), query)) {
				newList.addUniversityNode(current);

				if (matched == nullptr) {
					matched = current;
					matched->prev = nullptr;
					matched->next = nullptr;
				} else {
					matched->next = current;
					current->prev = matched;
					matched = current;
				}
			}
			current = currentNext;
		}
		return newList;
	}

	private:
	bool fuzzyMatch(const string& str, const string& query) {
		int strLen = str.length();
		int queryLen = query.length();
		int i = 0;
		int j = 0;

		while (i < strLen && j < queryLen) {
			if (tolower(str[i]) == tolower(query[j])) {
				i++;
				j++;
			} else {
				j = 0;				 // Reset query index
				i = i - j + 1; // Move back to the next character in str
			}
		}

		return (j == queryLen);
	}
};
