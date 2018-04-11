/*
Program 3 Part 4 Alternative
Team 3
Uslu and Xu
*/

#include "utility.h"

int main() {
	//read codes
	string codes[128] = {};
	ifstream ifile("codetable.txt");
	if (ifile) {
		string line, chr, code;
		unsigned int i, delimiter;
		while (getline(ifile, line)) {
			delimiter = line.find("\t");
			chr = line.substr(0, delimiter);
			code = line.substr(delimiter + 1);
			if (chr == "LF") {
				i = 10;
			}
			else if (chr == "Space") {
				i = 32;
			}
			else {
				i = static_cast<int>(chr[0]);
			}
			codes[i] = code;
		}
		ifile.close();
	}

	//read encoded text in binary
	ifstream cfile("codedalt.txt", ios::in | ios::binary);
	string codetext;
	if (cfile) {
		unsigned char c;
		while (cfile >> noskipws >> c) {
			bitset<8> byte;
			byte = static_cast<bitset<8>>(static_cast<int>(c));
			codetext += byte.to_string();
			//cout << byte << " " << static_cast<int>(c) << " " << c << endl;
		}
	}

	//decode text using brute-force
	string plaintext, cstr;
	for (char& c : codetext) {
		cstr += c;
		for (int i = 0; i < 128; i++) {
			if (codes[i] != "" && codes[i] == cstr) {
				plaintext += static_cast<char>(i);
				cstr = "";
				//cout << i << " " << static_cast<char>(i) << endl;
				break;
			}
		}
	}

	//check with clear.txt
	ifstream clearfile("clear.txt");
	string cleartext;
	char c;
	if (clearfile) {
		while (clearfile >> noskipws >> c) {
			cleartext += c;
		}
		clearfile.close();
	}

	for (unsigned int i = 0; i < cleartext.size(); i++) {
		if (cleartext[i] != plaintext[i]) {
			cout << "Error at position " << i << " " << cleartext[i] << " " << plaintext[i] << endl;
			system("pause");
		}
	}

	//write to output
	string outputfile = "decodedalt.txt";
	ofstream ofile(outputfile);
	if (ofile.is_open()) {
		ofile << plaintext;
		ofile.close();
	}
	
	cout << "Decoded binary file" << endl;

	system("pause");
	return 0;
}