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

class newMergeSort {
	public:
	universityNode* mergeSortString(universityNode* head, string column) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}

		universityNode* middle = getMiddleNode(head);
		universityNode* nextToMiddle = middle->next;
		middle->next = nullptr;

		universityNode* left = mergeSortString(head, column);
		universityNode* right = mergeSortString(nextToMiddle, column);

		return mergeString(left, right, column);
	}

	universityNode* mergeString(universityNode* left, universityNode* right, string column) {
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		universityNode* result = nullptr;

		if (getColumn(left, column) <= getColumn(right, column)) {
			result = left;
			result->next = mergeString(left->next, right, column);
		} else {
			result = right;
			result->next = mergeString(left, right->next, column);
		}

		return result;
	}

	universityNode* mergeSortInt(universityNode* head, string column) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}

		universityNode* middle = getMiddleNode(head);
		universityNode* nextToMiddle = middle->next;
		middle->next = nullptr;

		universityNode* left = mergeSortInt(head, column);
		universityNode* right = mergeSortInt(nextToMiddle, column);

		return mergeInt(left, right, column);
	}

	universityNode* mergeInt(universityNode* left, universityNode* right, string column) {
		if (left == nullptr) {
			return right;
		}
		if (right == nullptr) {
			return left;
		}

		universityNode* result = nullptr;

		if (stringToInt(getColumn(left, column)) <= stringToInt(getColumn(right, column))) {
			result = left;
			result->next = mergeInt(left->next, right, column);
		} else {
			result = right;
			result->next = mergeInt(left, right->next, column);
		}

		return result;
	}

	universityNode* getMiddleNode(universityNode* head) {
		if (head == nullptr) {
			return nullptr;
		}

		universityNode* slow = head;
		universityNode* fast = head->next;

		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}

		return slow;
	}

	int stringToInt(const string& str) {
		int result = 0;
		int sign = 1;
		int i = 0;

		if (str[i] == '-') {
			sign = -1;
			i++;
		}

		while (i < str.length()) {
			result = result * 10 + (str[i] - '0');
			i++;
		}

		return result * sign;
	}
};

class newQuickSort {
	public:
    universityNode* quicksortString(universityNode* head, universityNode* tail, string column) {
        if (head == nullptr || head == tail || tail == nullptr) {
            return head;
        }

        universityNode* pivot = partitionString(head, tail, column);

        if (pivot != head) {
            universityNode* prev = nullptr;
            universityNode* curr = head;

            while (curr != pivot) {
                prev = curr;
                curr = curr->next;
            }

            if (prev != nullptr) {
                prev->next = nullptr;
                head = quicksortString(head, prev, column);
                prev = getTail(head);
                prev->next = pivot;
            } else {
                head = quicksortString(head, pivot, column);
            }
        }

        pivot->next = quicksortString(pivot->next, tail, column);

        return head;
    }

	universityNode* quicksortInt(universityNode* head, universityNode* tail, string column) {
		if (head == nullptr || head == tail || tail == nullptr) {
			return head;
		}

		universityNode* pivot = partitionInt(head, tail, column);

		if (pivot != head) {
			universityNode* prev = nullptr;
			universityNode* curr = head;

			while (curr != pivot) {
				prev = curr;
				curr = curr->next;
			}

			if (prev != nullptr) {
				prev->next = nullptr;
				if (head != nullptr) {  // Add this check
					head = quicksortInt(head, prev, column);
					prev = getTail(head);
					prev->next = pivot;
				}
			} else {
				head = quicksortInt(head, pivot, column);
			}
		}

		if (pivot != nullptr) {  // Add this check
			pivot->next = quicksortInt(pivot->next, tail, column);
		}

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
