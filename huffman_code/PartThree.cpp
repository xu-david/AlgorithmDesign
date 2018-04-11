//part 3 from group 2
#include "utility.h"

// Returns the integer ASCII value for a character. Can also handle certain special cases.
int getASCII(string input) {
	if (input.length() == 1) {
		return static_cast<int>(input.at(0));
	}
	if (input == "LF") { //LF is a placeholder for the linefeed character
		return 10;
	}
	if (input == "Space") { //Space is a placeholder for space character
		return 32;
	}
	cout << "Error reading ASCII for input value: " << input << endl;
	exit(EXIT_FAILURE);
}

map<int, string>* BuildMapFromFile(string filename) {
	map<int, string> *codeMap = new map<int, string>();
	ifstream ifile(filename);
	string line, charStr, codeStr, delimeter = "\t";
	while (getline(ifile, line)) {
		charStr = line.substr(0, line.find(delimeter));
		codeStr = line.substr(line.find(delimeter) + delimeter.length());
		codeMap->insert(pair<int, string>(getASCII(charStr), codeStr));
	}
	return codeMap;
}

void EncodeFile(string inFilename, string outFilename, map<int, string> *codeMap) {
	ifstream infile(inFilename);
	ofstream ofile(outFilename);
	string code;
	char c;
	while (!infile.eof() && infile.get(c)) {
		// find the code associated with the charachter
		code = codeMap->find(static_cast <int> (c))->second;
		ofile << code;
	}
}

int main() {
	map<int, string> *codeMap = BuildMapFromFile("codetable.txt");
	EncodeFile("clear.txt", "coded.txt", codeMap);
	return 0;
}