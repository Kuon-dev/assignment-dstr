
#include "../Modules/Conversions.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <iomanip>

using namespace std;

struct universityNode {
	int Rank;
	string Name;
	string LocationCode;
	string Location;
	string ArScore;
	string ArRank;
	string ErScore;
	string ErRank;
	string FsrScore;
	string FsrRank;
	string CpfScore;
	string CpfRank;
	string IfrScore;
	string IfrRank;
	string IsrScore;
	string IsrRank;
	string IrnScore;
	string IrnRank;
	string GerScore;
	string GerRank;
	string ScoreScaled;
	universityNode* prev = nullptr;
	universityNode* next = nullptr;
};

//
// ==================================
// |
// | Code below is a doubly Linked List
// |
// |

class universityList {
	universityNode* head = nullptr;
	universityNode* tail = nullptr;

	public:
	// Add a new node to the end of the list
	void createUniversity(
		int rank,
		string name,
		string locationCode,
		string location,
		string arScore,
		string arRank,
		string erScore,
		string erRank,
		string fsrScore,
		string fsrRank,
		string cpfScore,
		string cpfRank,
		string ifrScore,
		string ifrRank,
		string isrScore,
		string isrRank,
		string irnScore,
		string irnRank,
		string gerScore,
		string gerRank,
		string scoreScaled) {
		universityNode* newNode = new universityNode;
		newNode->Rank = rank;
		newNode->Name = name;
		newNode->LocationCode = locationCode;
		newNode->Location = location;
		newNode->ArScore = arScore;
		newNode->ArRank = arRank;
		newNode->ErScore = erScore;
		newNode->ErRank = erRank;
		newNode->FsrScore = fsrScore;
		newNode->FsrRank = fsrRank;
		newNode->CpfScore = cpfScore;
		newNode->CpfRank = cpfRank;
		newNode->IfrScore = ifrScore;
		newNode->IfrRank = ifrRank;
		newNode->IsrScore = isrScore;
		newNode->IsrRank = isrRank;
		newNode->IrnScore = irnScore;
		newNode->IrnRank = irnRank;
		newNode->GerScore = gerScore;
		newNode->GerRank = gerRank;
		newNode->ScoreScaled = scoreScaled;
		newNode->prev = tail;

		if (tail != nullptr) {
			tail->next = newNode;
		} else {
			head = newNode;
		}
		tail = newNode;
	}

	void addUniversityNode(universityNode* newNode) {
		newNode->prev = tail;
		newNode->next = nullptr;
		if (head == nullptr) {
			head = tail = newNode;
		} else {
			tail->next = newNode;
			tail = newNode;
		}
	};

	// Get a node by rank
	universityNode* getUniversityByRank(int rank) {
		universityNode* current = head;
		while (current != nullptr) {
			if (current->Rank == rank) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	};

	void displayFirst20Nodes() {
		universityNode* current = head;
		if (head == nullptr) {
			cout << "The uni list is empty." << endl;
			return;
		}

		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
		cout << setw(6) << "Rank" << setw(60) << "Name" << setw(20) << "Location" << setw(12) << "AR Score" << setw(12)
				 << "AR Rank" << setw(12) << "ER Score" << setw(12) << "IrsScore" << endl;
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;

		int count = 0;
		while (current != nullptr && count < 20) {
			cout << setw(6) << current->Rank << setw(60) << current->Name << setw(20) << current->Location << setw(12)
					 << current->ArScore << setw(12) << current->ArRank << setw(12) << current->ErScore << setw(12)
					 << current->IsrScore << endl;
			current = current->next;
			count++;
		}
		cout << "----------------------------------------------------------------------------------------------------------"
				 << endl;
	}

	void quicksort() {
		if (head != nullptr && head != tail) quickSortHelper(head, tail);
	}

	void updateUniversityByRank(int rank) {
		universityNode* current = head;
		while (current != nullptr && current->Rank != rank) {
			current = current->next;
		}
		if (current == nullptr) {
			cout << "University with rank " << rank << " not found." << endl;
			return;
		}
		string ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank,
			IrnScore, IrnRank, GerScore, GerRank;
		string ScoreScaled;
		cout << "Enter AR score: ";
		cin >> ArScore;
		cout << "Enter AR rank: ";
		cin >> ArRank;
		cout << "Enter ER score: ";
		cin >> ErScore;
		cout << "Enter ER rank: ";
		cin >> ErRank;
		cout << "Enter FSR score: ";
		cin >> FsrScore;
		cout << "Enter FSR rank: ";
		cin >> FsrRank;
		cout << "Enter CPF score: ";
		cin >> CpfScore;
		cout << "Enter CPF rank: ";
		cin >> CpfRank;
		cout << "Enter IFR score: ";
		cin >> IfrScore;
		cout << "Enter IFR rank: ";
		cin >> IfrRank;
		cout << "Enter ISR score: ";
		cin >> IsrScore;
		cout << "Enter ISR rank: ";
		cin >> IsrRank;
		cout << "Enter IRN score: ";
		cin >> IrnScore;
		cout << "Enter IRN rank: ";
		cin >> IrnRank;
		cout << "Enter GER score: ";
		cin >> GerScore;
		cout << "Enter GER rank: ";
		cin >> GerRank;
		cout << "Enter Score Scaled: ";
		cin >> ScoreScaled;

		current->ArScore = ArScore;
		current->ArRank = ArRank;
		current->ErScore = ErScore;
		current->ErRank = ErRank;
		current->FsrScore = FsrScore;
		current->FsrRank = FsrRank;
		current->CpfScore = CpfScore;
		current->CpfRank = CpfRank;
		current->IfrScore = IfrScore;
		current->IfrRank = IfrRank;
		current->IsrScore = IsrScore;
		current->IsrRank = IsrRank;
		current->IrnScore = IrnScore;
		current->IrnRank = IrnRank;
		current->GerScore = GerScore;
		current->GerRank = GerRank;
		current->ScoreScaled = ScoreScaled;

		cout << "University with rank " << rank << " has been updated." << endl;
	}

	private:
	// helper functions
	void quickSortHelper(universityNode* left, universityNode* right) {
		if (right != nullptr && left != right && left != right->next) {
			universityNode* pivot = partition(left, right);
			quickSortHelper(left, pivot->prev);
			quickSortHelper(pivot->next, right);
		}
	}

	universityNode* partition(universityNode* left, universityNode* right) {
		double pivot = stringToDouble(right->ScoreScaled);
		universityNode* i = left->prev;
		for (universityNode* j = left; j != right; j = j->next) {
			double currentScore = stringToDouble(j->ScoreScaled);
			if (currentScore <= pivot) {
				i = (i == nullptr) ? left : i->next;
				swapNodes(i, j);
			}
		}
		i = (i == nullptr) ? left : i->next;
		swapNodes(i, right);
		return i;
	}

	void swapNodes(universityNode* node1, universityNode* node2) {
		if (node1 != node2) {
			// swap prev pointers
			universityNode* temp = node1->prev;
			node1->prev = node2->prev;
			node2->prev = temp;
			if (node1->prev == nullptr) {
				head = node1;
			} else {
				node1->prev->next = node1;
			}
			if (node2->prev == nullptr) {
				head = node2;
			} else {
				node2->prev->next = node2;
			}

			// swap next pointers
			temp = node1->next;
			node1->next = node2->next;
			node2->next = temp;
			if (node1->next == nullptr) {
				tail = node1;
			} else {
				node1->next->prev = node1;
			}
			if (node2->next == nullptr) {
				tail = node2;
			} else {
				node2->next->prev = node2;
			}
		}
	}
};
