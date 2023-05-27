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

	void updateFeedback(string feedbackId, string newContent) {
		feedbackNode* current = head;
		while (current != nullptr && current->FeedbackId != feedbackId) {
			current = current->NextAddress;
		}
		if (current == nullptr) {
			cout << "Feedback with ID " << feedbackId << " not found" << endl;
		} else {
			current->FeedbackContent = newContent;
			current->Timestamp = time(nullptr);
			cout << "Feedback with ID " << feedbackId << " updated" << endl;
		}
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

	feedbackNode* getHead() { return head; }
	feedbackNode* getTail() { return tail; }

	void sortFeedbackByUserId() {
		head = mergeSort(head);
		// update the tail pointer if necessary
		feedbackNode* current = head;
		while (current && current->NextAddress) {
			current = current->NextAddress;
		}
		tail = current;
	}

	private:
	feedbackNode* head;
	feedbackNode* tail;

	feedbackNode* merge(feedbackNode* leftList, feedbackNode* rightList) {
		feedbackNode* mergedList = nullptr;
		if (leftList == nullptr) {
			return rightList;
		} else if (rightList == nullptr) {
			return leftList;
		}
		if (leftList->UserId <= rightList->UserId) {
			mergedList = leftList;
			mergedList->NextAddress = merge(leftList->NextAddress, rightList);
		} else {
			mergedList = rightList;
			mergedList->NextAddress = merge(leftList, rightList->NextAddress);
		}
		mergedList->NextAddress->PreviousAddress = mergedList;
		return mergedList;
	}

	feedbackNode* mergeSort(feedbackNode* currentHead) {
		if (currentHead == nullptr || currentHead->NextAddress == nullptr) {
			return currentHead;
		}
		feedbackNode* middle = getMiddle(currentHead);
		feedbackNode* nextToMiddle = middle->NextAddress;
		middle->NextAddress = nullptr;
		feedbackNode* leftList = mergeSort(currentHead);
		feedbackNode* rightList = mergeSort(nextToMiddle);
		return merge(leftList, rightList);
	}

	feedbackNode* getMiddle(feedbackNode* currentHead) {
		feedbackNode* slowPtr = currentHead;
		feedbackNode* fastPtr = currentHead->NextAddress;
		while (fastPtr != nullptr) {
			fastPtr = fastPtr->NextAddress;
			if (fastPtr != nullptr) {
				slowPtr = slowPtr->NextAddress;
				fastPtr = fastPtr->NextAddress;
			}
		}
		return slowPtr;
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
