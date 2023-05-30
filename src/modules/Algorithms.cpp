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

bool isValidInteger(const string& value) {
    if (value.empty()) {
        return false;  // Empty value is not a valid integer
    }

    // Check for a leading "+" or "-"
    size_t start = 0;
    if (value[0] == '+' || value[0] == '-') {
        start = 1;  // Skip the leading sign
    }

    // Check if the remaining characters are digits
    for (size_t i = start; i < value.length(); ++i) {
        if (!isdigit(value[i])) {
            return false;  // Non-digit character found, not a valid integer
        }
    }

    return true;  // All characters are digits, valid integer
}

double stringToDouble(string s) {
	if (s.empty()) return 0.0;

	try {
		// convert string to double with decimal point
		return stod(s);
	} catch (const invalid_argument& e) {
		// handle invalid input string
		return 0.0;
	}
}

string toLower(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
	size_t firstNonSpace = s.find_first_not_of(' ');

	if (firstNonSpace != string::npos) {
		return s.erase(0, firstNonSpace);
	}
	return s;
}

// for uni
string getColumn(universityNode* node, string column) {
	if (column == "Rank") return to_string(node->Rank);
	else if (column == "Name") {
		// delete leading white-spaces
		string name = node->Name;
		size_t startPos = name.find_first_not_of(" \t");  // Find the position of the first non-whitespace character
		if (startPos != string::npos) {
			return name.substr(startPos);  // Return the substring starting from the first non-whitespace character
		}
		return name;  // If the string contains only whitespaces, return the original value without modification
	}
	else if (column == "LocationCode") return node->LocationCode;
	else if (column == "Location") return node->Location;
	else if (column == "ArScore") return isValidInteger(node->ArScore) ? node->ArScore : "0";
	else if (column == "ArRank") return isValidInteger(node->ArRank) ? node->ArRank : "0";
	else if (column == "ErScore") return isValidInteger(node->ErScore) ? node->ErScore : "0";
	else if (column == "ErRank") return isValidInteger(node->ErRank) ? node->ErRank : "0";
	else if (column == "FsrScore") return isValidInteger(node->FsrScore) ? node->FsrScore : "0";
	else if (column == "FsrRank") return isValidInteger(node->FsrRank) ? node->FsrRank : "0";
	else if (column == "CpfScore") return isValidInteger(node->CpfScore) ? node->CpfScore : "0";
	else if (column == "CpfRank") return isValidInteger(node->CpfRank) ? node->CpfRank : "0";
	else if (column == "IfrScore") return isValidInteger(node->IfrScore) ? node->IfrScore : "0";
	else if (column == "IfrRank") return isValidInteger(node->IfrRank) ? node->IfrRank : "0";
	else if (column == "IsrScore") return isValidInteger(node->IsrScore) ? node->IsrScore : "0";
	else if (column == "IsrRank") return isValidInteger(node->IsrRank) ? node->IsrRank : "0";
	else if (column == "IrnScore") return isValidInteger(node->IrnScore) ? node->IrnScore : "0";
	else if (column == "IrnRank") return isValidInteger(node->IrnRank) ? node->IrnRank : "0";
	else if (column == "GerScore") return isValidInteger(node->GerScore) ? node->GerScore : "0";
	else if (column == "GerRank") return isValidInteger(node->GerRank) ? node->GerRank : "0";
	else if (column == "ScoreScaled") return node->ScoreScaled;
	else return "";
}

string getColumnFromIndex(int index) {
	switch (index) {
	case 0:
		return "Rank";
	case 1:
		return "Name";
	case 2:
		return "LocationCode";
	case 3:
		return "Location";
	case 4:
		return "ArScore";
	case 5:
		return "ArRank";
	case 6:
		return "ErScore";
	case 7:
		return "ErRank";
	case 8:
		return "FsrScore";
	case 9:
		return "FsrRank";
	case 10:
		return "CpfScore";
	case 11:
		return "CpfRank";
	case 12:
		return "IfrScore";
	case 13:
		return "IfrRank";
	case 14:
		return "IsrScore";
	case 15:
		return "IsrRank";
	case 16:
		return "IrnScore";
	case 17:
		return "IrnRank";
	case 18:
		return "GerScore";
	case 19:
		return "GerRank";
	case 20:
		return "ScoreScaled";
	default:
		throw runtime_error("Invalid index for column.");
	}
}

void setColumn(universityNode* node, string column, string value) {
	if (column == "Rank") node->Rank = stoi(value);
	else if (column == "Name") node->Name = value;
	else if (column == "LocationCode") node->LocationCode = value;
	else if (column == "Location") node->Location = value;
	else if (column == "ArScore") node->ArScore = value;
	else if (column == "ArRank") node->ArRank = value;
	else if (column == "ErScore") node->ErScore = value;
	else if (column == "ErRank") node->ErRank = value;
	else if (column == "FsrScore") node->FsrScore = value;
	else if (column == "FsrRank") node->FsrRank = value;
	else if (column == "CpfScore") node->CpfScore = value;
	else if (column == "CpfRank") node->CpfRank = value;
	else if (column == "IfrScore") node->IfrScore = value;
	else if (column == "IfrRank") node->IfrRank = value;
	else if (column == "IsrScore") node->IsrScore = value;
	else if (column == "IsrRank") node->IsrRank = value;
	else if (column == "IrnScore") node->IrnScore = value;
	else if (column == "IrnRank") node->IrnRank = value;
	else if (column == "GerScore") node->GerScore = value;
	else if (column == "GerRank") node->GerRank = value;
	else if (column == "ScoreScaled") node->ScoreScaled = value;
	else if (column == "all") {
		int currentIndex = 0, previousIndex = 0, counter = 0;
		while ((currentIndex = value.find(',', currentIndex)) != string::npos) {
			string element = value.substr(previousIndex, currentIndex - previousIndex);
			setColumn(node, getColumnFromIndex(counter), element);
			currentIndex++;
			previousIndex = currentIndex;
			counter++;
		}
		// Last element after the last comma.
		string lastElement = value.substr(previousIndex);
		setColumn(node, getColumnFromIndex(counter), lastElement);
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
	private:
	universityNode* SortedMerge(universityNode* a, universityNode* b, string column) {
		universityNode* result = nullptr;

		if (a == nullptr) return (b);
		else if (b == nullptr) return (a);

		// Sorting by name in ascending order.
		if (getColumn(a, column) <= getColumn(b, column)) {
			result = a;
			result->next = SortedMerge(a->next, b, column);
			if (result->next) {
				result->next->prev = result;
			}
			result->prev = nullptr;
		}
		// If names are same then sort by rank in descending order.
		else {
			result = b;
			result->next = SortedMerge(a, b->next, column);
			if (result->next) {
				result->next->prev = result;
			}
			result->prev = nullptr;
		}
		return (result);
	}

	universityNode* Split(universityNode* head) {
		universityNode *fast = head, *slow = head;
		while (fast->next && fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		universityNode* temp = slow->next;
		slow->next = nullptr;
		return temp;
	}

	universityNode* MergeSort(universityNode* head, string column) {
		if (!head || !head->next) return head;
		universityNode* second = Split(head);

		// Recur for left and right halves.
		head = MergeSort(head, column);
		second = MergeSort(second, column);

		// Merge the two sorted halves.
		return SortedMerge(head, second, column);
	}

	// SortedMerge function specialized for integers.
	universityNode* SortedMergeInt(universityNode* a, universityNode* b, string column, string order) {
		universityNode* result = nullptr;

		if (a == nullptr) return b;
		else if (b == nullptr) return a;

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

		if (result->next) result->next->prev = result;

		return result;
	}

	// MergeSort function specialized for integers.
	universityNode* MergeSortInt(universityNode* head, string column, string order) {
		if (!head || !head->next) return head;
		universityNode* second = Split(head);

		// Recur for left and right halves.
		head = MergeSortInt(head, column, order);
		second = MergeSortInt(second, column, order);

		// Merge the two sorted halves.
		return SortedMergeInt(head, second, column, order);
	}

	public:
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

	void mergeSortString(universityList& uList, string column) {
		universityNode* newHead = MergeSort(uList.getHead(), column);
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
	private:
	// The function to find the partition position
	universityNode* partitionString(universityNode* low, universityNode* high, string column, string order) {
		// set rightmost element as pivot
		string pivot = getColumn(high, column);

		// pointer for the greater element
		universityNode* i = low->prev;

		// traverse each node of the list
		for (universityNode* j = low; j != high; j = j->next) {
			if ((order == "asc" && getColumn(j, column) <= pivot) || (order == "dsc" && getColumn(j, column) >= pivot)) {
				// swapNodes nodes at i and j
				i = (i == nullptr) ? low : i->next;
				swapNodes(i, j);
			}
		}
		// swap the pivot node with the greater node specified by i
		i = (i == nullptr) ? low : i->next;
		swapNodes(i, high);

		// return the node i
		return i;
	}

	void quickSortString(universityNode* low, universityNode* high, string column, string order) {
		if (high != nullptr && low != high && low != high->next) {
			universityNode* p = partitionString(low, high, column, order);
			quickSortString(low, p->prev, column, order);
			quickSortString(p->next, high, column, order);
		}
	}

	universityNode* partitionInt(universityNode* low, universityNode* high, string column, string order) {
		// set rightmost element as pivot
		int pivot = stoi(getColumn(high, column));

		// pointer for the greater element
		universityNode* i = low->prev;

		// traverse each node of the list
		for (universityNode* j = low; j != high; j = j->next) {
			if (
				(order == "asc" && stoi(getColumn(j, column)) <= pivot)
				|| (order == "dsc" && stoi(getColumn(j, column)) >= pivot)) {
				// swapNodes nodes at i and j
				i = (i == nullptr) ? low : i->next;
				swapNodes(i, j);
			}
		}
		// swap the pivot node with the greater node specified by i
		i = (i == nullptr) ? low : i->next;
		swapNodes(i, high);

		// return the node i
		return i;
	}

	void quickSortInt(universityNode* low, universityNode* high, string column, string order) {
		if (high != nullptr && low != high && low != high->next) {
			universityNode* p = partitionInt(low, high, column, order);
			quickSortInt(low, p->prev, column, order);
			quickSortInt(p->next, high, column, order);
		}
	}

	void swapNodes(universityNode* a, universityNode* b) {
		if (a == nullptr || b == nullptr) {
			throw runtime_error("Cannot swap null nodes");
		}

		// Create a temporary node to hold values of node a
		universityNode temp = *a;

		// Swap fields in the universityNode
		a->Rank = b->Rank;
		a->Name = b->Name;
		a->LocationCode = b->LocationCode;
		a->Location = b->Location;
		a->ArScore = b->ArScore;
		a->ArRank = b->ArRank;
		a->ErScore = b->ErScore;
		a->ErRank = b->ErRank;
		a->FsrScore = b->FsrScore;
		a->FsrRank = b->FsrRank;
		a->CpfScore = b->CpfScore;
		a->CpfRank = b->CpfRank;
		a->IfrScore = b->IfrScore;
		a->IfrRank = b->IfrRank;
		a->IsrScore = b->IsrScore;
		a->IsrRank = b->IsrRank;
		a->IrnScore = b->IrnScore;
		a->IrnRank = b->IrnRank;
		a->GerScore = b->GerScore;
		a->GerRank = b->GerRank;
		a->ScoreScaled = b->ScoreScaled;

		// Copy values from temporary node to node b
		b->Rank = temp.Rank;
		b->Name = temp.Name;
		b->LocationCode = temp.LocationCode;
		b->Location = temp.Location;
		b->ArScore = temp.ArScore;
		b->ArRank = temp.ArRank;
		b->ErScore = temp.ErScore;
		b->ErRank = temp.ErRank;
		b->FsrScore = temp.FsrScore;
		b->FsrRank = temp.FsrRank;
		b->CpfScore = temp.CpfScore;
		b->CpfRank = temp.CpfRank;
		b->IfrScore = temp.IfrScore;
		b->IfrRank = temp.IfrRank;
		b->IsrScore = temp.IsrScore;
		b->IsrRank = temp.IsrRank;
		b->IrnScore = temp.IrnScore;
		b->IrnRank = temp.IrnRank;
		b->GerScore = temp.GerScore;
		b->GerRank = temp.GerRank;
		b->ScoreScaled = temp.ScoreScaled;
	}

	public:
	void quicksortInt(universityList& uList, string column, string order) {
		quickSortInt(uList.getHead(), uList.getTail(), column, order);
	}
	void quicksortString(universityList& uList, string column) {
		quickSortString(uList.getHead(), uList.getTail(), column, "asc");
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
	universityNode* binarySearch(universityList* list, string field, int query) {
		int length;
		universityNode** array = linkedListToArray(list, length);
		universityNode* result = binarySearch(array, length, field, query);
		delete[] array;
		return result;
	}

	universityNode* binarySearch(universityList* list, string field, string query) {
		int length;
		universityNode** array = linkedListToArray(list, length);
		universityNode* result = binarySearch(array, length, field, query);
		delete[] array;
		return result;
	}

	universityList* linearSearch(universityNode* head, string column, string query) {
		universityList* newList = new universityList;
		universityNode* current = head;
		universityNode* currentNext = nullptr;

		while (current != nullptr) {
			currentNext = current->next; // Assign next node before moving current

			if (fuzzyMatch(getColumn(current, column), query)) {
				// Deep copy the node.
				universityNode* newNode = new universityNode(*current);
				newNode->next = nullptr;
				newNode->prev = newList->getTail();
				if (newList->getHead() == nullptr) {
					newList->setHead(newNode);
				}
				if (newList->getTail() != nullptr) {
					newList->getTail()->next = newNode;
				}
				newList->setTail(newNode);
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
	universityNode** linkedListToArray(universityList* list, int& length) {
		length = 0;
		universityNode* current = list->getHead();
		while (current != nullptr) {
			length++;
			current = current->next;
		}

		universityNode** array = new universityNode*[length];
		current = list->getHead();
		for (int i = 0; i < length; i++) {
			array[i] = current;
			current = current->next;
		}
		return array;
	}
	// int type
	universityNode* binarySearch(universityNode** array, int length, string field, int query) {
		int start = 0, end = length - 1;
		while (start <= end) {
			int mid = start + (end - start) / 2;
			int midValue = stoi(getColumn(array[mid], field));  // Use '.' instead of '->*'
			if (midValue == query) {
				return array[mid];
			} else if (midValue < query) {
				start = mid + 1;
			} else {
				end = mid - 1;
			}
		}
		return nullptr;
	}
	// string type
	universityNode* binarySearch(universityNode** array, int length, string field, const string& query) {
		int start = 0, end = length - 1;
		while (start <= end) {
			int mid = start + (end - start) / 2;
			string midValue = getColumn(array[mid], field);
			int comparison = midValue.compare(query);
			if (comparison == 0) {
				return array[mid];
			} else if (comparison < 0) {
				start = mid + 1;
			} else {
				end = mid - 1;
			}
		}
		return nullptr;
	}

};
