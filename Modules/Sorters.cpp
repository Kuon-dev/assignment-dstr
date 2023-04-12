#include "../Models/University.cpp"

// ---------------------------------
// This section contains list of helper functions
//
// ---------------------------------

// for uni
string getColumn(universityNode* node, string column) {
	if (column == "Name") {
		return node->Name;
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


// ---------------------------------
// quick sort algorithm for uni
//
// ---------------------------------

class universitySorter {
	public:
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
		double pivot = stringToDouble(getColumn(tail, "ArScore"));
		universityNode* i = head->prev;

		for (universityNode* j = head; j != tail; j = j->next) {
			if (stringToDouble(getColumn(j, "ArScore")) <= pivot) {
				i = (i == nullptr) ? head : i->next;
				swapNodes(i, j);
			}
		}
		i = (i == nullptr) ? head : i->next;
		swapNodes(i, tail);
		return i;
	}

	// Recursive function for quicksort
	void quickSortUniversity(universityNode* head, universityNode* tail, string column) {
		if (tail != nullptr && head != tail && head != tail->next) {
			universityNode* p = partition(head, tail, column);
			quickSortUniversity(head, p->prev, column);
			quickSortUniversity(p->next, tail, column);
		}
	}
};

// ---------------------------------
// This file contains the list of sorters
//
//
// ---------------------------------
//
