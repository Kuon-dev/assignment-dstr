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

class universityMergeSort {
	public:
	// merge sort
	universityNode* mergeSortUniversityInt(universityNode** head, string column) {
		universityNode* current = *head;
		universityNode* left;
		universityNode* right;

		if (*head == nullptr || (*head)->next == nullptr) {
			return current; // Base case: list is empty or has only one node
		}

		splitList(current, &left, &right);
		left = mergeSortUniversityInt(&left, column);
		right = mergeSortUniversityInt(&right, column);
		return mergeByColumn(left, right, column);
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
	// Partition function for quicksort
};

class universityQuickSort {
	public:
	void quicksortInt(universityNode* head, universityNode* tail, string column) {
		if (tail != nullptr && head != tail && head != tail->next) {
			universityNode* p = partition(head, tail, column);
			quicksortInt(head, p->prev, column);
			quicksortInt(p->next, tail, column);
		}
	}

	universityNode* quicksortString(universityNode* head, universityNode* tail, string column) {
		if (head == nullptr || head == tail) {
			return head;
		}

		// Partition the list and get the pivot node
		universityNode* pivot = partitionString(head, tail, column);

		// Recursively sort the two sublists
		if (pivot != head) {
			universityNode* prev = head;
			while (prev->next != pivot) {
				prev = prev->next;
			}
			prev->next = nullptr;
			head = quicksortString(head, prev, column);
			prev = getTail(head);
			prev->next = pivot;
		}
		pivot->next = quicksortString(pivot->next, tail, column);

		return head;
	}

	private:
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
			if (toLower(getColumn(j, column)).compare(toLower(pivot)) <= 0) {
				i = (i == nullptr) ? head : i->next;
				swapNodes(i, j);
			}
		}

		i = (i == nullptr) ? head : i->next;
		swapNodes(i, tail);

		return i;
	}

	void swapNodes(universityNode* node1, universityNode* node2) {
		string temp;

		temp = node1->Name;
		node1->Name = node2->Name;
		node2->Name = temp;

		temp = node1->LocationCode;
		node1->LocationCode = node2->LocationCode;
		node2->LocationCode = temp;

		temp = node1->Location;
		node1->Location = node2->Location;
		node2->Location = temp;

		temp = node1->ArScore;
		node1->ArScore = node2->ArScore;
		node2->ArScore = temp;

		temp = node1->ArRank;
		node1->ArRank = node2->ArRank;
		node2->ArRank = temp;

		temp = node1->ErScore;
		node1->ErScore = node2->ErScore;
		node2->ErScore = temp;

		temp = node1->ErRank;
		node1->ErRank = node2->ErRank;
		node2->ErRank = temp;

		temp = node1->FsrScore;
		node1->FsrScore = node2->FsrScore;
		node2->FsrScore = temp;

		temp = node1->FsrRank;
		node1->FsrRank = node2->FsrRank;
		node2->FsrRank = temp;

		temp = node1->CpfScore;
		node1->CpfScore = node2->CpfScore;
		node2->CpfScore = temp;

		temp = node1->CpfRank;
		node1->CpfRank = node2->CpfRank;
		node2->CpfRank = temp;

		temp = node1->IfrScore;
		node1->IfrScore = node2->IfrScore;
		node2->IfrScore = temp;

		temp = node1->IfrRank;
		node1->IfrRank = node2->IfrRank;
		node2->IfrRank = temp;

		temp = node1->IsrScore;
		node1->IsrScore = node2->IsrScore;
		node2->IsrScore = temp;

		temp = node1->IsrRank;
		node1->IsrRank = node2->IsrRank;
		node2->IsrRank = temp;

		temp = node1->IrnScore;
		node1->IrnScore = node2->IrnScore;
		node2->IrnScore = temp;

		temp = node1->IrnRank;
		node1->IrnRank = node2->IrnRank;
		node2->IrnRank = temp;

		temp = node1->GerScore;
		node1->GerScore = node2->GerScore;
		node2->GerScore = temp;

		temp = node1->GerRank;
		node1->GerRank = node2->GerRank;
		node2->GerRank = temp;

		temp = node1->ScoreScaled;
		node1->ScoreScaled = node2->ScoreScaled;
		node2->ScoreScaled = temp;
	}

	universityNode* getTail(universityNode* head) {
		if (head == nullptr) {
			return nullptr;
		}
		while (head->next != nullptr) {
			head = head->next;
		}
		return head;
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
