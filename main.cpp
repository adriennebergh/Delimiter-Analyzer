#include <iostream>
#include <stdexcept>
#include <fstream>
#include <exception>
#include "GenStack.h"

using namespace std;

int main(int argc, char **argv) {

	bool choice = true;
	string fileName;

	fileName = argv[1];

	while(choice) {

		ifstream file;
		file.open(fileName);
		//test to make sure file has opened. If not, re-enter file name.
		while (!file.is_open()) {
			cout << "Error opening file." << endl;
			cout << "Re-type file name: " << endl;
			getline(cin, fileName);
			file.open(fileName);
		}

		GenStack<char> stack(20);
		GenStack<int> lineNumbers(20);
		
		string line;
		int lineNumber = 1;
		while(getline(file, line)) {
			char c;
			
			for (int i=0; i<line.length(); ++i) {
				c = line[i];
				switch(c) {
					case '{':
						stack.push('{');
						lineNumbers.push(lineNumber);
						break;
					case '[':
						stack.push('[');
						lineNumbers.push(lineNumber);
						break;
					case '(':
						stack.push('(');
						lineNumbers.push(lineNumber);
						break;
					case '}':

						if(stack.isEmpty()) {
							cout << "Line " << lineNumber << ": Unaccompanied }." << endl;
							exit(0);
						}

						else if (stack.peak() != '{') {

							if (lineNumbers.peak() != lineNumber) {
								if (stack.peak() == '(') {
									cout << "Missing ) at line " << lineNumbers.peak() << endl;
									//cout << "Line " << lineNumbers.peak() << ": Found ( where { should occur." << endl;
									//If a { is swapped for a (, the above line should execute. When the missing ) occurs at the end of the file, there is no way to distinguish between the case of a missing ) or a missplaced (
									exit(0);
								}
								else if (stack.peak() == '[') {
									cout << "Missing ] at line " << lineNumbers.peak() << endl;
									//cout << "Line " << lineNumbers.peak() << ": Found [ where { should occur." << endl;
									exit(0);
								}
							}
							else {
								if (stack.peak() == '[') {
									cout << "Line " << lineNumber << ": Found } where ] should occur." << endl;
									exit(0);
								}
								else if (stack.peak() == '(') {
									cout << "Line " << lineNumber << ": Found } where ) should occur." << endl;
									exit(0);
								}
							}
						}
						else if (stack.peak() == '{') {
							try {
								stack.pop();
								lineNumbers.pop();
							//if the stack is empty, throw Empty Stack exception
							} catch (exception &e) {
							cout << e.what() << endl;
							}	
						}
						break;
					case ']':
						if(stack.isEmpty()) {
							cout << "Line " << lineNumber << ": Unaccompanied ]." << endl;
							exit(0);
						}
						//if the current line number is not equal to the line number of the stack.peak() char
							//missing a [ at line number current line number
						//else
							//the char that is there is the wrong one
						if (stack.peak() != '[') {
							if (lineNumbers.peak() != lineNumber) {
								if (stack.peak() == '{') {
									cout << "Line " << lineNumber << ": Found ] where } should occur." << endl;
									exit(0);
								}								
								else if (stack.peak() == '(') {
									cout << "Missing ) at line " << lineNumbers.peak() << endl;
									exit(0);
								}
							}
							else {
								if (stack.peak() == '{') {
									cout << "Line " << lineNumber << ": Found ] where } should occur." << endl;
									exit(0);
								}
								else if (stack.peak() == '(') {
									cout << "Line " << lineNumber << ": Found ] where ) should occur." << endl;
									exit(0);
								}
							}
						}
						else {
							try {
								stack.pop();
								lineNumbers.pop();
							} catch (exception &e) {
							cout << e.what() << endl;
							}	
						}
						
						break;
					case ')':
						if (stack.isEmpty()) {
							cout << "Line " << lineNumber << ": Unaccompanied )." << endl;
							exit(0);
						}
						else if (stack.peak() != '(') {
							if (lineNumbers.peak() != lineNumber) {
								cout << "Missing ( at line " << lineNumber << endl;
								exit(0);
							}
							else {
								if (stack.peak() == '{') {
									cout << "Line " << lineNumber << ": Found ) where } should occur." << endl;
									exit(0);
								}
								else if (stack.peak() == '[') {
									cout << "Line " << lineNumber << ": Found ) where ] should occur." << endl;
									exit(0);
								}
							}
						}
						else if (stack.peak() == '(') {
							try {
								stack.pop();
								lineNumbers.pop();
							} catch (exception &e) {
							cout << e.what() << endl;
							}	
						}
						break;
				}
			}
			++lineNumber;
			
		}

		if(file.eof()) {
			if(!stack.isEmpty()) {
				if (stack.peak() == '{') {
					cout << "Reached end of file. Missing a }" << endl;
				}
				else if(stack.peak() == '(') {
					cout << "Unaccompanied ( at line: " << lineNumbers.peak() << endl;
				}
				else if(stack.peak() == '{') {
					cout << "Unaccompanied { at line: " << lineNumbers.peak() << endl;
				}
				exit(0);
			}
		}

		file.close();

		cout << "Congratulations! Your file has no delimiter errors. Would you like to analyze another file? (yes/no) " << endl;

		string response;
		getline(cin, response);

		while(!(response == "yes" || response == "no")) {
			cout << "Please type yes or no." << endl;
			getline(cin, response);
		}

		if(response == "yes") {
			cout << "Type new file name: " << endl;
			getline(cin, fileName);
		}

		else if(response == "no") {
			choice = false;
		}

	} 

	return 0;
}
