#include <iostream>
#include <string>

using namespace std;

string toLower(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = std::tolower(s[i]);
	}
	return s;
}
