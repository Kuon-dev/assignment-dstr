#include "../Models/University.cpp"

class UniversityContoller {
	public:
	universityList readUniversityDatabase() {
		universityList* list = new universityList();
		ifstream file("Database/Universities.csv");
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

			string Rank, Name, LocationCode, Location, ArScore, ArRank, ErScore, ErRank, FsrScore, FsrRank, CpfScore, CpfRank,
				IfrScore, IfrRank, IsrScore, IsrRank, IrnScore, IrnRank, GerScore, GerRank, ScoreScaled;

			string token;

			getline(iss, token, ',');
			int rank = stoi(token);

			getline(iss, token, ',');
			Name = token;

			getline(iss, token, ',');
			LocationCode = token;

			getline(iss, token, ',');
			Location = token;

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
	};

	void displayFist20Uni() {
		universityList newList = readUniversityDatabase();
		newList.displayFirst20Nodes();
	}
};
