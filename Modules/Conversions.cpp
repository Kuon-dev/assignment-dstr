#include <iostream>
#include <string>

using namespace std;

string removeSpecialChars(string str) {
	string result = "";
	for (char c: str) {
		if (isdigit(c) || c == '.' || c == '-') {
			result += c;
		}
	}
	return result;
}

double stringToDouble(string s) {
	if (s.empty()) {
		return 0.0;
	}

	// remove any non-numeric characters except for '.' and '-'
	string temp = removeSpecialChars(s);

	// handle special cases such as "+", "-" and "."
	if (temp == "+" || temp == "-") {
		return 0.0;
	}

	bool hasDecimal = false;
	int decimalPlace = 0;

	for (size_t i = 0; i < temp.length(); ++i) {
		if (temp[i] == '.') {
			if (hasDecimal) {
				// multiple decimal places, invalid
				return 0.0;
			}
			hasDecimal = true;
			decimalPlace = i;
		} else if (temp[i] == '-' && i != 0) {
			// minus sign not at the start of the string, invalid
			return 0.0;
		} else if (!isdigit(temp[i])) {
			// non-numeric character, invalid
			return 0.0;
		}
	}
	if (hasDecimal) {
		// convert string to double with decimal point
		return stod(temp);
	} else {
		// convert string to integer
		return stoi(temp);
	}
}
