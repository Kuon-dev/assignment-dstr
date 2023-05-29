#include "../Modules/Algorithms.cpp"
#include <chrono>

using namespace std::chrono;
class UniversityContoller {
	public:
	universityList* readUniversityDatabase() {
		universityList* list = new universityList();
		// ifstream file("C:/Users/Acer/source/repos/assignment-dstr/Database/Universities.csv");
		ifstream file("Database/Universities.csv");
		if (!file.is_open()) {
			cout << "\033[31m"
					 << "Error: could not open uni file "
					 << "\033[0m" << endl;
			return list;
		}
		// skip header
		string header;
		getline(file, header);

		string line;
		while (getline(file, line)) {
			stringstream iss(line);
			universityNode* node = new universityNode();

			string ArScore;
			string Rank, Name, LocationCode, Location, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank,
				IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;

			string token;

			getline(iss, token, ',');
			int rank = stoi(token);

			getline(iss, token, ',');
			//(token[0] == '\"') ? Name = token.substr(1, token.size() - 2) : Name = token;
			if (token[0] == '\"') {
				// Handle cases where the location contains a comma
				while (token[token.size() - 1] != '\"') {
					std::string temp;
					std::getline(iss, temp, ',');
					token += "," + temp;
				}
				Name = token.substr(1, token.size() - 2);
			} else Name = token;

			getline(iss, token, ',');
			LocationCode = token;

			getline(iss, token, ',');
			if (token[0] == '\"') {
				// Handle cases where the location contains a comma
				while (token[token.size() - 1] != '\"') {
					std::string temp;
					std::getline(iss, temp, ',');
					token += "," + temp;
				}
				Location = token.substr(1, token.size() - 2);
			} else Location = token;

			getline(iss, token, ',');
			ArScore = (token);

			getline(iss, token, ',');
			ArRank = (token);

			getline(iss, token, ',');
			ErScore = (token);

			getline(iss, token, ',');
			ErRank = (token);

			getline(iss, token, ',');
			FsrScore = (token);

			getline(iss, token, ',');
			FsrRank = (token);

			getline(iss, token, ',');
			CpfScore = (token);

			getline(iss, token, ',');
			CpfRank = (token);

			getline(iss, token, ',');
			IfrScore = (token);

			getline(iss, token, ',');
			IfrRank = (token);

			getline(iss, token, ',');
			IsrScore = (token);

			getline(iss, token, ',');
			IsrRank = (token);

			getline(iss, token, ',');
			IrnScore = (token);

			getline(iss, token, ',');
			IrnRank = (token);

			getline(iss, token, ',');
			GerScore = (token);

			getline(iss, token, ',');
			GerRank = (token);

			getline(iss, token, ',');
			ScoreScaled = (token);

			node->Rank = (rank);
			node->Name = Name;
			node->LocationCode = LocationCode;
			node->Location = Location;
			node->ArScore = (ArScore);
			node->ArRank = (ArRank);
			node->ErScore = (ErScore);
			node->ErRank = (ErRank);
			node->FsrScore = (FsrScore);
			node->FsrRank = (FsrRank);
			node->CpfScore = (CpfScore);
			node->CpfRank = (CpfRank);
			node->IfrScore = (IfrScore);
			node->IfrRank = (IfrRank);
			node->IsrScore = (IsrScore);
			node->IsrRank = (IsrRank);
			node->IrnScore = (IrnScore);
			node->IrnRank = (IrnRank);
			node->GerScore = (GerScore);
			node->GerRank = (GerRank);
			if(ScoreScaled == "-") {
				ScoreScaled = "0";
			}
			node->ScoreScaled = ScoreScaled;

			list->addUniversityNode(node);
		};

		file.close();
		return list;
	};

	void displayPaginated(universityList list, int index) { list.displayPaginated(index); }

	void displayAll(universityList list) { list.displayAll(); }

	void searchUniversityColumn(string column, int input, universityList* currentList) {
		universityList* queryList = new universityList();
		newMergeSort mergeSorter;
		universitySearcher searcher;

		mergeSorter.mergeSortString(*currentList, column);
		queryList = searcher.binarySearch(currentList,(input));
		queryList->displayPaginated(1);
	}

	void searchUniMerge(string column, string input, universityList* currentList) {
		newMergeSort newMerge;
		universitySearcher searcher;

		universityNode* head = currentList->getHead();
		newMerge.mergeSortString(*currentList, column);
		universityList* filteredList = new universityList;
		filteredList = searcher.linearSearch(currentList->getHead(), column, (input));
		filteredList->displayAll();
	}

	void searchUniQuick(string column, string input, universityList* currentList) {
		newMergeSort sorter;
		newQuickSort quickSort;
		universitySearcher searcher;

		universityNode* head = currentList->getHead();
		universityNode* tail = currentList->getTail();
		(quickSort.quicksortString(*currentList, column));

		// sort ends, start search
		universityList* filteredList = new universityList;
		filteredList = searcher.linearSearch(currentList->getHead(), column, (input));
		filteredList->displayAll();
	}
};
