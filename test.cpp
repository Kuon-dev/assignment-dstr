#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream csvFile("./Database/Universities.csv"); // open the CSV file
	string line;

	while (getline(csvFile, line)) { // read each line of the file
		string column;
		int i = 0;

		while (i < line.length()) { // loop through each character in the line
			if (line[i] == ',') {			// if comma is encountered, add column to array
				cout << column << endl;
				column = "";							 // reset column value
			} else if (line[i] == '"') { // if double quote is encountered, add column to array until end quote is found
				i++;
				while (line[i] != '"') {
					column += line[i];
					i++;
				}
			} else { // add character to column value
				column += line[i];
			}

			i++;
		}

		cout << column << endl; // print the last column value
	}

	csvFile.close(); // close the file
	return 0;
}
