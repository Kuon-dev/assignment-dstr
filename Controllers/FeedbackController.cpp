#include "../Models/UserFeedback.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FeedbackController {
	public:
	// initialize new feedback
	int createFeedback() {
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

		ofstream outfile("Database/FeedbackDatabase.csv", ios::app);
		if (outfile) {
			outfile << feedback->FeedbackId << "," << feedback->UserId << "," << feedback->FeedbackContent << ","
							<< feedback->Timestamp << endl;
			outfile.close();
		} else {
			cerr << "Error opening file." << endl;
			return 1;
		}

		cout << "Feedback created and stored in database." << endl;
		return 0;
	}

	void updateFeedback(string feedbackId, string newContent) {
		ofstream tempFile("temp.csv");
		ifstream file("Database/FeedbackDatabase.csv");
		string line;
		bool found = false;
		while (getline(file, line)) {
			istringstream iss(line);
			string id, userId, content, timestamp;
			getline(iss, id, ',');
			getline(iss, userId, ',');
			getline(iss, content, ',');
			getline(iss, timestamp, ',');
			if (id == feedbackId) {
				found = true;
				tempFile << id << "," << userId << "," << newContent << "," << timestamp << endl;
			} else {
				tempFile << line << endl;
			}
		}
		file.close();
		tempFile.close();
		if (found) {
			remove("Database/FeedbackDatabase.csv");
			rename("temp.csv", "Database/FeedbackDatabase.csv");
			cout << "Feedback with ID " << feedbackId << " updated." << endl;
		} else {
			remove("temp.csv");
			cout << "Feedback with ID " << feedbackId << " not found." << endl;
		}
	}

	feedbackNode* getFeedbackById(string feedbackId) {
		ifstream file("Database/FeedbackDatabase.csv");
		string line;
		while (getline(file, line)) {
			cout << feedbackId << endl;
			istringstream iss(line);
			string id, userId, content, timestamp;
			getline(iss, id, ',');
			getline(iss, userId, ',');
			getline(iss, content, ',');
			getline(iss, timestamp, ',');
			if (id == feedbackId) {
				try {
					feedbackNode* feedback = new feedbackNode;
					feedback->FeedbackId = id;
					feedback->UserId = userId;
					feedback->FeedbackContent = content;
					feedback->Timestamp = stoi(timestamp);
					file.close();
					return feedback;
				} catch (std::bad_alloc& e) {
					cerr << "Error allocating memory: " << e.what() << endl;
					return nullptr;
				}
			}
		}
		file.close();
		cout << "Feedback with ID " << feedbackId << " not found." << endl;
		return nullptr;
	};

	void readFeedbackById(string feedbackId) {
		feedbackList newFeedbackList;
		feedbackNode newFeedback;

		feedbackNode* feedback = getFeedbackById(feedbackId);
		if (feedback != nullptr) {
			newFeedbackList.retrieveFeedback(
				newFeedback.UserId, newFeedback.FeedbackId, newFeedback.FeedbackContent, newFeedback.Timestamp);
			newFeedbackList.displayFeedback(feedback);
		}
	};


	int readAllFeedbacks() {
		feedbackList feedback;
		ifstream file("Database/FeedbackDatabase.csv");
		if (file) {
			cout << left << setw(15) << "Feedback ID" << setw(15) << "User ID" << setw(50) << "Feedback Content" << setw(30)
					 << "Timestamp" << endl;
			string line;
			while (getline(file, line)) {
				stringstream ss(line);
				string feedbackId, userId, feedbackContent, timestamp;
				getline(ss, feedbackId, ',');
				getline(ss, userId, ',');
				getline(ss, feedbackContent, ',');
				getline(ss, timestamp, ',');

				feedback.retrieveFeedback(feedbackId, userId, feedbackContent, stoi(timestamp));
			}
			file.close();
		} else {
			cerr << "Error opening file." << endl;
			return 0;
		}
		feedback.displayAllFeedback();
		return 1;
	}

	void deleteFeedback(string feedbackId) {
		// open the file for reading
		ifstream inFile(databaseFileName);
		if (!inFile.is_open()) {
			cout << "Error: could not open file " << databaseFileName << endl;
			return;
		}

		// read the file line by line, copying all lines that don't match the ID to a new file
		ofstream outFile(tempFileName);
		if (!outFile.is_open()) {
			cout << "Error: could not open file " << tempFileName << endl;
			inFile.close();
			return;
		}

		string line;
		bool feedbackDeleted = false;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string field;
			getline(ss, field, ','); // get the feedback ID field

			if (field == feedbackId) {
				feedbackDeleted = true;
			} else {
				outFile << line << endl;
			}
		}

		// close both files and delete the original file
		inFile.close();
		outFile.close();
		remove(databaseFileName.c_str());

		// rename the temporary file to the original name
		rename(tempFileName.c_str(), databaseFileName.c_str());

		if (feedbackDeleted) {
			cout << "Feedback with ID " << feedbackId << " has been deleted." << endl;
		} else {
			cout << "Feedback with ID " << feedbackId << " not found." << endl;
		}
	}

	private:
	string databaseFileName = ".Database.FeedbackDatabase.csv";
	string tempFileName = "temp.csv";
};
