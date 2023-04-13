#include "../Controllers/FeedbackController.cpp"
#include <iostream>

void feedbackMenu() {
	FeedbackController controller;
	int choice = -1;
	string feedbackId;
	feedbackNode* feedback;
	string UserId = "uu036";
	while (choice != 0) {
		cout << "Enter your choice:" << endl;
		cout << "1. Create feedback" << endl;
		cout << "2. Display feedback by ID" << endl;
		cout << "3. Display all feedback" << endl;
		cout << "4. Update feedback" << endl;
		cout << "5. Delete feedback" << endl;
		cout << "0. Exit" << endl;
		cin >> choice;
		cin.ignore(); // Ignore newline character from previous input

		switch (choice) {
		case 1: {
			controller.createFeedback();
			cout << "Feedback created." << endl;
			break;
		}
		case 2: {
			cout << "Enter feedback ID:" << endl;
			getline(cin, feedbackId);
			controller.readFeedbackById(feedbackId);
			break;
		}

		case 3: {
			controller.readAllFeedbacks();
			break;
		};
		case 4: {
			cout << "Enter feedback ID:" << endl;
			string feedbackId;
			getline(cin, feedbackId);
			feedbackNode* feedback = controller.getFeedbackById(feedbackId);
			if (feedback != nullptr) {
				cout << "Enter new feedback content:" << endl;
				string newContent;
				getline(cin, newContent);
				controller.updateFeedback(feedbackId, newContent);
			}
			break;
		}
		case 5: {
			cout << "Enter feedback ID:" << endl;
			string feedbackId;
			getline(cin, feedbackId);
			controller.deleteFeedback(feedbackId);
			break;
		}
		case 0: {
			cout << "Exiting feedback menu." << endl;
			break;
		}
		default: {
			cout << "Invalid choice, please try again." << endl;
			break;
		}
		}
	}
}
