/*======================================================================*
*	Aim: To count the frequency of the ASCII characters from the file.	*
*	Team 0: Keyur Mehta, Danny Pham										*
*	!Fixed by Team 3													*
*=======================================================================*/

#include "utility.h"

class Huffman_code {
	ifstream f;
	ofstream fr;

	int i;
	int j;
	int n = 128;
	int temp;
	char c;
	int char_freq[128];

public:
	void read_file() {

		f.open("clear.txt");

		if (f.fail())       //check file name is valid or not
		{
			cout << "Invalid file name.." << endl;
			system("pause");
			exit(0);
		}

		for (i = 0; i < n; i++) //initialize all frequency with 0
			char_freq[i] = 0;

		if (f.is_open()) {
			cout << "Clear.text file is being read and calculation of frequency count is started..." << endl << endl;
			while (!f.eof() && f.get(c)) {    //read the file char by char and count the frequency.

				temp = static_cast <int> (c);
				char_freq[temp]++;
			}
		}

		f.close();

	} //read_file

	void write_freq() {
		fr.open("freq.txt");

		for (i = 0; i < n; i++) {
			if (char_freq[i] != 0)
			{
				// if statement for linefeed character
				if (i == 10)
				{
					fr << "LF" << "\t" << char_freq[i] << endl;
				}
				// if statement for carriage return 
				else if (i == 13)
				{
					fr << "CR" << "\t" << char_freq[i] << endl;
				}
				/*
				// if statement for space
				else if (i == 32)
				{
					fr << " " << "\t";
					fr << char_freq[i] << endl;
				}*/
				// other ASCII characters
				else
				{
					fr << static_cast <char> (i) << "\t" << char_freq[i] << endl;
				}
			}
		}
		cout << "Frequency count of charachters is calculated and written in the file freq.txt" << endl;
		fr.close();
	} //write_freq

};


int main() {

	Huffman_code hc;

	hc.read_file();

	hc.write_freq();

	system("pause");
}