#include "../Models/Feedback.cpp"
#include "../Models/Member.cpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class FeedbackController {
	public:
	// initialize new feedback
	feedbackList* readFeedbackDatabase() {
		feedbackList* list = new feedbackList(); // Allocate memory for the feedbackList

		ifstream file("Database/FeedbackDatabase.csv"); // get user database
		// validate file open
		if (!file.is_open()) {
			cout << "\033[31m"
					 << "Error: could not open file "
					 << "\033[0m" << endl;
			return list;
		}
		// define database header and line
		string header, line;
		getline(file, header);
		while (getline(file, line)) {
			stringstream iss(line);
			feedbackNode* node = new feedbackNode(); // Allocate memory for the node

			string FeedbackId, UserId, FeedbackContent, ReplyContent;
			time_t Timestamp;

			string token; // to get value

			getline(iss, token, ',');
			FeedbackId = token;

			getline(iss, token, ',');
			UserId = token;

			getline(iss, token, ',');
			FeedbackContent = token;

			getline(iss, token, ',');
			ReplyContent = token;

			getline(iss, token, ',');
			Timestamp = static_cast<time_t>(stoi(token));

			node->UserId = UserId;
			node->FeedbackId = FeedbackId;
			node->FeedbackContent = FeedbackContent;
			node->ReplyContent = ReplyContent;
			node->Timestamp = Timestamp;
			list->addFeedbackNode(node);
		}

		file.close();
		return list;
	}
	void writeToDatabase(feedbackList* list) {
		ofstream outputFile("Database/FeedbackDatabase.csv");

		if (outputFile.is_open()) {
			outputFile << "FeedbackId,UserId,FeedbackContent,ReplyContent,Timestamp" << endl;

			feedbackNode* current = list->getHead();
			while (current != nullptr) {
				outputFile << current->FeedbackId << ",";
				outputFile << current->UserId << ",";
				outputFile << current->FeedbackContent << ",";
				outputFile << current->ReplyContent << ",";
				outputFile << to_string(current->Timestamp) << endl;
				current = current->NextAddress;
			}

			outputFile.close();
			cout << "Feedback data successfully saved " << endl;
		} else {
			cout << "Error: Unable to open the file " << endl;
		}
	};

	feedbackNode* getFeedbackById(feedbackList* list, string feedbackId) {
		feedbackNode* current = list->getHead();
		while (current != nullptr) {
			if (current->FeedbackId == feedbackId) return current;
			current = current->NextAddress;
		}
		return nullptr;
	};

	feedbackList* getFeedbacksByUser(feedbackList* list, userNode* node) {
		feedbackList* feedback = new feedbackList;
		feedbackNode* current = list->getHead();
		while (current != nullptr) {
			if (current->UserId == node->UserId) feedback->addFeedbackNode(current);
			current = current->NextAddress;
		}
		return feedback;
	};

	void createFeedback(feedbackList* currentList, userNode* currentUser) {
		if (currentList == nullptr) {
			cout << "Invalid feedback list." << endl;
			return;
		}

		feedbackNode* newFeedback = new feedbackNode();
		string feedbackContent = handleStringInput("Enter your feedback: ");
		newFeedback->FeedbackId = to_string(createFeedbackId(currentList));
		newFeedback->UserId = currentUser->UserId;
		newFeedback->ReplyContent = "";
		newFeedback->FeedbackContent = feedbackContent;
		auto now = chrono::system_clock::now();
		newFeedback->Timestamp = chrono::system_clock::to_time_t(now);

		newFeedback->PreviousAddress = nullptr;
		newFeedback->NextAddress = nullptr;

		currentList->addFeedbackNode(newFeedback);
		cout << "Feedback created" << endl;
		return;
	};

	private:
	int createFeedbackId(feedbackList* data) {
		feedbackNode* lastNode = data->getTail();
		if (lastNode == nullptr) return 1;
		else if (lastNode->FeedbackId == "") return 1;
		else return (stoi(lastNode->FeedbackId) + 1);
	}
};
