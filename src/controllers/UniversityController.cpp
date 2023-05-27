#include "../Modules/Algorithms.cpp"
#include <chrono>

using namespace std::chrono;
class UniversityContoller {
	public:
	universityList* readUniversityDatabase() {
		universityList* list = new universityList();
		ifstream file("C:/Users/Acer/source/repos/assignment-dstr/Database/Universities.csv");
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
			node->ScoreScaled = ScoreScaled;

			list->addUniversityNode(node);
		};

		file.close();
		return list;
	};

	void displayPaginated(universityList list, int index) { list.displayPaginated(index); }

	void displayAll(universityList list) { list.displayAll(); }

	void searchUniversityColumn(string column, int input, universityList* currentList) {
		cout << "\033[94mFetching database...\033[0m" << endl;
		universityList queryList;
		universityQuickSort sorter;
		universitySearcher searcher;
		auto startTime = high_resolution_clock::now();

		cout << "\033[94mUsing Quick sort...\033[0m" << endl;
		sorter.quicksortString(currentList->getHead(), currentList->getTail(), "Name");

		auto endTime = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(endTime - startTime);

		cout << "\033[94mTime taken to sort: " << duration.count() << " milliseconds \033[0m" << endl;
		universityNode* searched = searcher.binarySearch(currentList->getHead(), column, (input));

		queryList.addUniversityNode(searched);
		queryList.displayAll();
	}

	void searchUniMerge(string column, string input, universityList* currentList) {
		universityMergeSort mergeSorter;
		universitySearcher searcher;

		cout << "\033[94mFetching database...\033[0m" << endl;

		cout << "\033[94mSorting list...\033[0m" << endl;
		cout << "\033[94mUsing Merge sort...\033[0m" << endl;
		auto sortStartTime = high_resolution_clock::now();
		universityNode* head = currentList->getHead();
		currentList->setHead(mergeSorter.mergeSortUniversityString(&head, "Name"));
		auto sortEndTime = high_resolution_clock::now();
		auto sortDuration = duration_cast<milliseconds>(sortEndTime - sortStartTime);
		cout << "\033[94mTime taken to sort: " << sortDuration.count() << " milliseconds\033[0m" << endl;
		cout << "\033[94mSearching database...\033[0m" << endl;
		auto searchStartTime = high_resolution_clock::now();
		universityList filteredList = searcher.linearSearch(currentList->getHead(), column, (input));
		auto endTime = high_resolution_clock::now();
		auto searchDuration = duration_cast<milliseconds>(endTime - searchStartTime);
		cout << "\033[94mTime taken to search: " << searchDuration.count() << " milliseconds\033[0m" << endl;
		filteredList.displayAll();
	}

	void searchUniQuick(string column, string input, universityList* currentList) {
		universityQuickSort sorter;
		universitySearcher searcher;

		cout << "\033[94mFetching database...\033[0m" << endl;

		// start sort
		cout << "\033[94mSorting list...\033[0m" << endl;
		cout << "\033[94mUsing Quick sort...\033[0m" << endl;
		auto sortStartTime = high_resolution_clock::now();
		universityNode* head = currentList->getHead();
		universityNode* tail = currentList->getTail();
		currentList->setHead(sorter.quicksortString(head, tail, column));
		auto sortEndTime = high_resolution_clock::now();
		auto sortDuration = duration_cast<milliseconds>(sortEndTime - sortStartTime);
		cout << "\033[94mTime taken to sort: " << sortDuration.count() << " milliseconds\033[0m" << endl;

		// sort ends, start search
		cout << "\033[94mSearching database...\033[0m" << endl;
		auto searchStartTime = high_resolution_clock::now();
		universityList filteredList = searcher.linearSearch(currentList->getHead(), column, (input));
		auto endTime = high_resolution_clock::now();
		auto searchDuration = duration_cast<milliseconds>(endTime - searchStartTime);
		cout << "\033[94mTime taken to search: " << searchDuration.count() << " milliseconds\033[0m" << endl;
		filteredList.displayAll();
	}

	universityList readUniversityDatabaseLinkedList() {
		universityList* list = new universityList();
		ifstream file("C:/Users/Acer/source/repos/assignment-dstr/Database/Universities.csv");
		if (!file.is_open()) {
			cout << "\033[31m"
					 << "Error: could not open file "
					 << "\033[0m" << endl;
			return *list;
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
			node->ScoreScaled = ScoreScaled;

			list->addUniversityNode(node);
		};

		file.close();
		return *list;
	}
};
