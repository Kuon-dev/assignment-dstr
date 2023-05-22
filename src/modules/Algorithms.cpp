#include "../Models/University.cpp"
#include <cctype>

/*
---------------------------------
| Helper function section
---------------------------------
| This section contains list of helper functions
|
*/

// for uni
string getColumn(universityNode* node, string column) {
	if (column == "Name") {
		return node->Name;
	} else if (column == "Rank") {
		return to_string(node->Rank);
	} else if (column == "LocationCode") {
		return node->LocationCode;
	} else if (column == "Location") {
		return node->Location;
	} else if (column == "ArRank") {
		return node->ArRank;
	} else if (column == "ArScore") {
		return node->ArScore;
	} else if (column == "ErRank") {
		return node->ErRank;
	} else if (column == "ErScore") {
		return node->ErScore;
	} else if (column == "FsrRank") {
		return node->FsrRank;
	} else if (column == "FsrScore") {
		return node->FsrScore;
	} else if (column == "CpfRank") {
		return node->CpfRank;
	} else if (column == "CpfScore") {
		return node->CpfScore;
	} else if (column == "IfrRank") {
		return node->IfrRank;
	} else if (column == "IfrScore") {
		return node->IfrScore;
	} else if (column == "IsrRank") {
		return node->IsrRank;
	} else if (column == "IsrScore") {
		return node->IsrScore;
	} else if (column == "IrnRank") {
		return node->IrnRank;
	} else if (column == "IrnScore") {
		return node->IrnScore;
	} else if (column == "GerRank") {
		return node->GerRank;
	} else if (column == "GerScore") {
		return node->GerScore;
	} else if (column == "ScoreScaled") {
		return node->ScoreScaled;
	} else {
		throw invalid_argument("Invalid column name");
	}
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

class universitySorter {
	public:
	// merge sort
	void mergeSortUniversityInt(universityNode** head, string column) {
		if (*head == nullptr || (*head)->next == nullptr) {
			return; // Base case: list is empty or has only one node
		}

		universityNode* middle = getMiddleNode(*head);
		universityNode* nextToMiddle = middle->next;
		middle->next = nullptr;

		mergeSortUniversityInt(head, column);					 // Sort the left half
		mergeSortUniversityInt(&nextToMiddle, column); // Sort the right half

		*head = mergeByColumn(*head, nextToMiddle, column); // Merge the sorted halves
	}

universityNode* mergeSortUniversityString(universityNode** head, string column) {
    universityNode* current = *head;
    universityNode* left;
    universityNode* right;

    if (current == nullptr || current->next == nullptr) {
        return current;
    }

    splitList(current, &left, &right);
    left = mergeSortUniversityString(&left, column);
    right = mergeSortUniversityString(&right, column);
    return mergeByStringColumn(left, right, column);
}
	// quick sort
	void quickSortUniversityInt(universityNode* head, universityNode* tail, string column) {
		if (tail != nullptr && head != tail && head != tail->next) {
			universityNode* p = partition(head, tail, column);
			quickSortUniversityInt(head, p->prev, column);
			quickSortUniversityInt(p->next, tail, column);
		}
	}

	void quickSortUniversityString(universityNode* head, universityNode* tail, string column) {
		if (tail != nullptr && head != tail && head != tail->next) {
			universityNode* pivot = partitionString(head, tail, column);
			quickSortUniversityString(head, pivot->prev, column);
			quickSortUniversityString(pivot->next, tail, column);
		}
	}

	private:
	universityNode* getMiddleNode(universityNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}

		universityNode* slow = head;
		universityNode* fast = head->next;

		while (fast != nullptr) {
			fast = fast->next;
			if (fast != nullptr) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		return slow;
	}

void splitList(universityNode* source, universityNode** front, universityNode** back) {
    universityNode* slow = source;
    universityNode* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

	universityNode* mergeByColumn(universityNode* left, universityNode* right, string column) {
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		universityNode* result = nullptr;

		if (getColumn(left, column) <= getColumn(right, column)) {
			result = left;
			result->next = mergeByColumn(left->next, right, column);
		} else {
			result = right;
			result->next = mergeByColumn(left, right->next, column);
		}

		return result;
	}

	universityNode* mergeByStringColumn(universityNode* left, universityNode* right, string column) {
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		universityNode* result = nullptr;

		if (toLower(getColumn(left, column)).compare(toLower(getColumn(right, column))) <= 0) {
			result = left;
			result->next = mergeByStringColumn(left->next, right, column);
		} else {
			result = right;
			result->next = mergeByStringColumn(left, right->next, column);
		}

		return result;
	}

	// quick sort section

	void swapNodes(universityNode* node1, universityNode* node2) {
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

	// Partition function for quicksort
	universityNode* partition(universityNode* head, universityNode* tail, string column) {
		double pivot = stringToDouble(getColumn(tail, column));
		universityNode* i = head->prev;

		for (universityNode* j = head; j != tail; j = j->next) {
			if (stringToDouble(getColumn(j, column)) <= pivot) {
				i = (i == nullptr) ? head : i->next;
				swapNodes(i, j);
			}
		}
		i = (i == nullptr) ? head : i->next;
		swapNodes(i, tail);
		return i;
	}

	universityNode* partitionString(universityNode* head, universityNode* tail, string column) {
		string pivot = getColumn(tail, column);
		universityNode* i = head->prev;

		for (universityNode* j = head; j != tail; j = j->next) {
			if (getColumn(j, column).compare(pivot) <= 0) {
				i = (i == nullptr) ? head : i->next;
				swapNodes(i, j);
			}
		}
		i = (i == nullptr) ? head : i->next;
		swapNodes(i, tail);
		return i;
	}

	string toLowerCase(string str) {
		for (char& c: str) {
			c = std::tolower(c);
		}
		return str;
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

			if (fuzzyMatch(current->Name, query)) {
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
