#include <iostream>
#include <fstream>
#include "GenStack.h"

using namespace std;

template<typename T>
void GenStack<T>::countDelims(string fileName) {

	ifstream file;
	file.open(fileName); 
	while (!file.is_open()) {
		cout << "Error opening file." << endl;
		cout << "Re-type file name: " << endl;
		getline(cin, fileName);
		file.open(fileName);
	}

	GenStack<char> stack(50);
	
	string line;
	while(getline(file, line)) {
		char c;
		for (int i=0; i<line.length(); ++i) {
			c = line[i];

			
		}

	file.close();

} 

