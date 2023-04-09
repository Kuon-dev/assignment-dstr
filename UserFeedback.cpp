#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

struct feedbackNode {
  feedbackNode* PreviousAddress;
  feedbackNode* NextAddress;
  string FeedbackId;
  string UserId;
  string FeedbackContent;
  time_t Timestamp;
} * head, * tail;

class feedbackList {
	public:
		feedbackList() : head(nullptr), tail(nullptr) {}

		void createFeedback(string userId, string feedbackContent) {
			feedbackNode* newFeedback = new feedbackNode;
			newFeedback->UserId = userId;
			newFeedback->FeedbackContent = feedbackContent;
			newFeedback->Timestamp = time(nullptr);
			newFeedback->PreviousAddress = tail;
			newFeedback->NextAddress = nullptr;
			if (head == nullptr) {
				head = tail = newFeedback;
			} else {
				tail->NextAddress = newFeedback;
				tail = newFeedback;
			}
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
			while (current != nullptr) {
				displayFeedback(current);
				current = current->NextAddress;
			}
		}

    feedbackNode* getHead() {
        return head;
    }

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
			}
			else if (rightList == nullptr) {
				return leftList;
			}
			if (leftList->UserId <= rightList->UserId) {
				mergedList = leftList;
				mergedList->NextAddress = merge(leftList->NextAddress, rightList);
			}
			else {
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
};

int main() {
	feedbackList feedbacks;
	feedbacks.createFeedback("uu056","this is a content");
	feedbacks.createFeedback("uu054","this is a content 2");
	feedbacks.createFeedback("uu059","this is a content 3");
	feedbacks.displayAllFeedback();
	feedbacks.sortFeedbackByUserId();
	cout << "=========" << endl;
	feedbacks.displayAllFeedback();

	return 0;
}
