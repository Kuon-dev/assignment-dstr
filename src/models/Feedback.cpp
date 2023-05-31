#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct feedbackNode {
	feedbackNode* PreviousAddress;
	feedbackNode* NextAddress;
	string FeedbackId;
	string UserId;
	string FeedbackContent;
	string ReplyContent;
	time_t Timestamp;

} *head, *tail;

class feedbackList {
	public:
	feedbackList(): head(nullptr), tail(nullptr) {}

	// add existing feedback from the database to the linked list
	int createFeedbackNode(string feedbackId, string userId, string content, time_t time) {
		feedbackNode* newFeedback = new feedbackNode;
		newFeedback->FeedbackId = feedbackId;
		newFeedback->UserId = userId;
		newFeedback->FeedbackContent = content;
		newFeedback->Timestamp = time;

		newFeedback->PreviousAddress = tail;
		newFeedback->NextAddress = nullptr;
		if (head == nullptr) {
			head = tail = newFeedback;
		} else {
			tail->NextAddress = newFeedback;
			tail = newFeedback;
		}
		return 0;
	}

	void addFeedbackNode(feedbackNode* newNode) {
		if (head == nullptr) {
			head = tail = newNode;
		} else {
			tail->NextAddress = newNode;
			newNode->PreviousAddress = tail;
			tail = newNode;
		};
	}

	void updateFeedback(feedbackNode* newNode) {
		if (head == nullptr) {
			cout << "The feedback list is empty." << endl;
			return;
		}

		feedbackNode* current = head;

		while (current != nullptr) {
			if (current->FeedbackId == newNode->FeedbackId) {
				newNode->PreviousAddress = current->PreviousAddress;
				newNode->NextAddress = current->NextAddress;

				if (current->PreviousAddress != nullptr) {
					current->PreviousAddress->NextAddress = newNode;
				} else {
					// Updating head node
					head = newNode;
				}

				if (current->NextAddress != nullptr) {
					current->NextAddress->PreviousAddress = newNode;
				} else {
					// Updating tail node
					tail = newNode;
				}

				delete current; // Delete the existing node
				break;
			}

			current = current->NextAddress;
		}
	}

	void updateFeedbackReply(feedbackNode* node, string content) {
		node->ReplyContent = content;
		updateFeedback(node);
	}

	feedbackNode* getFeedbackById(string feedbackId) {
		feedbackNode* current = head;
		while (current != nullptr && current->FeedbackId != feedbackId) {
			current = current->NextAddress;
		}
		if (current == nullptr) {
			cout << "Feedback with ID " << feedbackId << " not found" << endl;
		}
		return current;
	}

	void deleteFeedback(string feedbackId) {
		feedbackNode* current = head;
		while (current != nullptr && current->FeedbackId != feedbackId) {
			current = current->NextAddress;
		}
		if (current == nullptr) {
			cout << "Feedback with ID " << feedbackId << " not found" << endl;
		} else {
			if (current == head) {
				head = head->NextAddress;
			}
			if (current == tail) {
				tail = tail->PreviousAddress;
			}
			if (current->PreviousAddress != nullptr) {
				current->PreviousAddress->NextAddress = current->NextAddress;
			}
			if (current->NextAddress != nullptr) {
				current->NextAddress->PreviousAddress = current->PreviousAddress;
			}
			delete current;
			cout << "Feedback with ID " << feedbackId << " deleted" << endl;
		}
	}

	void displayFeedback(feedbackNode* feedback) {
		if (feedback != nullptr) {
			cout << "Feedback ID: " << feedback->FeedbackId << endl;
			cout << "User ID: " << feedback->UserId << endl;
			cout << "Feedback content: " << feedback->FeedbackContent << endl;

			tm timestamp_tm;
			localtime_s(&timestamp_tm, &feedback->Timestamp);
			cout << "Timestamp: " << std::put_time(&timestamp_tm, "%c %Z") << endl;
		}
	}

	void displayAllFeedback() {
		if (head == nullptr) {
			cout << "The feedback list is empty." << endl;
			return;
		}

		feedbackNode* current = head;

		printTableRow("Feedback ID", "Feedback Content", "Reply Content", "Time created");

		while (current != nullptr) {
			tm timestamp_tm;
			localtime_s(&timestamp_tm, &current->Timestamp);
			string feedbackContent = current->FeedbackContent;
			int width = 60; // Width limit for Feedback Content
			int startPos = 0;

			// Print the Feedback Content with wrapping
			while (startPos < feedbackContent.length()) {
				stringstream ss;
				ss << put_time(&timestamp_tm, "%c %Z");
				string formattedTimestamp = ss.str();
				int remainingWidth = std::min(width, static_cast<int>(feedbackContent.length() - startPos));
				printTableRow(
					current->FeedbackId,
					feedbackContent.substr(startPos, remainingWidth),
					current->ReplyContent,
					formattedTimestamp);
				startPos += width;
			}

			current = current->NextAddress; // Move to the next node
		}
	}

	void displayFeedbackPaginate(int pageNumber) {
		if (head == nullptr) {
			cout << "The feedback list is empty." << endl;
			return;
		}

		int count = 0;
		int startIdx = (pageNumber - 1) * 5;
		int endIdx = startIdx + 5;

		feedbackNode* current = head;
		printTableRow("Feedback ID", "Feedback Content", "Reply Content", "Time created");
		while (current != nullptr && count < endIdx) {
			if (count >= startIdx) {
				tm timestamp_tm;
				localtime_s(&timestamp_tm, &current->Timestamp);
				string feedbackContent = current->FeedbackContent;
				int width = 60; // Width limit for Feedback Content
				int startPos = 0;

				// Print the Feedback Content with wrapping
				while (startPos < feedbackContent.length()) {
					stringstream ss;
					ss << put_time(&timestamp_tm, "%c %Z");
					string formattedTimestamp = ss.str();
					int remainingWidth = std::min(width, static_cast<int>(feedbackContent.length() - startPos));
					printTableRow(
						current->FeedbackId,
						feedbackContent.substr(startPos, remainingWidth),
						current->ReplyContent,
						formattedTimestamp);
					startPos += width;
				}
			}

			current = current->NextAddress; // Move to the next node
			count++;
		}

		if (count < startIdx) {
			cout << "Invalid page number. There are fewer feedbacks than the requested page." << endl;
		}
	}

	feedbackNode* getHead() { return head; }
	feedbackNode* getTail() { return tail; }
	void setHead(feedbackNode* newHead) { head = newHead; }

	private:
	feedbackNode* head;
	feedbackNode* tail;

	feedbackNode* getFeedbackNodeById(feedbackList* data, string id) {
		feedbackNode* current = data->getHead();
		while (current != nullptr) {
			if (current->FeedbackId == id) return current;
			current = current->NextAddress;
		};
		return nullptr;
	}

	private:
	void
	printTableRow(const std::string& col1, const std::string& col2, const std::string& col3, const std::string& col4) {
		int col1Width = 15;
		int col2Width = 60;
		int col3Width = 50;
		int col4Width = 30;

		std::cout << std::left << std::setw(col1Width) << col1.substr(0, col1Width - 1) << " | " << std::setw(col2Width)
							<< col2.substr(0, col2Width - 1) << " | " << std::setw(col3Width) << col3.substr(0, col3Width - 1)
							<< " | " << std::setw(col4Width) << col4.substr(0, col4Width - 1) << std::endl;

		std::cout << std::setfill('-') << std::setw(col1Width + col2Width + col3Width + col4Width + 9) << ""
							<< std::setfill(' ') << std::endl;
	}
};
