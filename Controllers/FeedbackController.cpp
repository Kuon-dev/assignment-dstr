#include "../Models/UserFeedback.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FeedbackController
{
	public:
	int createFeedback()
	{
		string userId, feedbackContent;
		cout << "Enter user ID: ";
		cin >> userId;
		cin.ignore(); // consume the newline character left in the input stream

		cout << "Enter feedback content: ";
		getline(cin, feedbackContent);

		time_t now = time(nullptr);
		feedbackList newFeedback;
		newFeedback.createFeedback(userId, feedbackContent);

		feedbackNode* feedback = newFeedback.getHead();

		ofstream outfile("FeedbackDatabase.csv", ios::app);
		if (outfile)
		{
			outfile << feedback->FeedbackId << "," << feedback->UserId << "," << feedback->FeedbackContent << ","
							<< feedback->Timestamp << endl;
			outfile.close();
		}
		else
		{
			cerr << "Error opening file." << endl;
			return 1;
		}

		cout << "Feedback created and stored in database." << endl;
		return 0;
	}

	void updateFeedback(string feedbackId, string newContent)
	{
		ofstream tempFile("temp.csv");
		ifstream file("FeedbackDatabase.csv");
		string line;
		bool found = false;
		while (getline(file, line))
		{
			istringstream iss(line);
			string id, userId, content, timestamp;
			getline(iss, id, ',');
			getline(iss, userId, ',');
			getline(iss, content, ',');
			getline(iss, timestamp, ',');
			if (id == feedbackId)
			{
				found = true;
				tempFile << id << "," << userId << "," << newContent << "," << timestamp << endl;
			}
			else
			{
				tempFile << line << endl;
			}
		}
		file.close();
		tempFile.close();
		if (found)
		{
			remove("FeedbackDatabase.csv");
			rename("temp.csv", "FeedbackDatabase.csv");
			cout << "Feedback with ID " << feedbackId << " updated." << endl;
		}
		else
		{
			remove("temp.csv");
			cout << "Feedback with ID " << feedbackId << " not found." << endl;
		}
	}

	feedbackNode* retrieveFeedback(string feedbackId)
	{
		ifstream file("FeedbackDatabase.csv");
		string line;
		while (getline(file, line))
		{
			istringstream iss(line);
			string id, userId, content, timestamp;
			getline(iss, id, ',');
			getline(iss, userId, ',');
			getline(iss, content, ',');
			getline(iss, timestamp, ',');
			if (id == feedbackId)
			{
				feedbackNode* feedback = new feedbackNode;
				feedback->FeedbackId = id;
				feedback->UserId = userId;
				feedback->FeedbackContent = content;
				feedback->Timestamp = stoi(timestamp);
				file.close();
				return feedback;
			}
		}
		file.close();
		cout << "Feedback with ID " << feedbackId << " not found." << endl;
		return nullptr;
	};

	void deleteFeedback(string feedbackId)
	{
		// open the file for reading
		ifstream inFile(databaseFileName);
		if (!inFile.is_open())
		{
			cout << "Error: could not open file " << databaseFileName << endl;
			return;
		}

		// read the file line by line, copying all lines that don't match the ID to a new file
		ofstream outFile(tempFileName);
		if (!outFile.is_open())
		{
			cout << "Error: could not open file " << tempFileName << endl;
			inFile.close();
			return;
		}

		string line;
		bool feedbackDeleted = false;
		while (getline(inFile, line))
		{
			stringstream ss(line);
			string field;
			getline(ss, field, ','); // get the feedback ID field

			if (field == feedbackId)
			{
				feedbackDeleted = true;
			}
			else
			{
				outFile << line << endl;
			}
		}

		// close both files and delete the original file
		inFile.close();
		outFile.close();
		remove(databaseFileName.c_str());

		// rename the temporary file to the original name
		rename(tempFileName.c_str(), databaseFileName.c_str());

		if (feedbackDeleted)
		{
			cout << "Feedback with ID " << feedbackId << " has been deleted." << endl;
		}
		else
		{
			cout << "Feedback with ID " << feedbackId << " not found." << endl;
		}
	}

	private:
	string databaseFileName = "FeedbackDatabase.csv";
	string tempFileName = "temp.csv";
};
