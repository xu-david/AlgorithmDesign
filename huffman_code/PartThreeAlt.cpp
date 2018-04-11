/*
Program 3 Part 3 Alternative
Team 3
Uslu and Xu
*/

#include "utility.h"

int main() {
	//read code array
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
			//cout << chr << " " << i << " " << code << endl;
			codes[i] = code;
		}
		ifile.close();
	}

	//read clear
	ifstream cfile("clear.txt");
	unsigned char c;
	string codetext;
	if (cfile.is_open()) {
		while (cfile >> noskipws >> c) {
			int intc = static_cast<int>(c);
			string code = codes[intc];
			codetext = codetext + code;
			//cout << c << " " << intc << " " << code << endl;
		}
		cfile.close();
	}

	//write to output
	ofstream ofile("codedalt.txt", ios::binary);
	if (ofile.is_open()) {
		string sbyte;
		for (char& c : codetext) {
			sbyte += c;
			if (sbyte.size() == 8) {
				bitset<8> byte(sbyte);
				//cout << byte << " " << byte.to_ulong() << " " << static_cast<char>(byte.to_ulong()) << endl;
				ofile << static_cast<char>(byte.to_ulong());
				sbyte = "";
			}
		}

		//pad the last byte
		while (sbyte.size() < 8) {
			sbyte += "0";
		}
		bitset<8> byte(sbyte);
		ofile << static_cast<char>(byte.to_ulong());
	}
	cout << "Wrote coded file in binary" << endl;
	system("pause");
	return 0;
}