#include "utility.h"
#include "filer.h"

int next_number(int range) {
	//return random number in range [0, range]
	int x = rand() % (range + 1);
	return x;
}

void makefile(int n, int range, string filename) {
	//write n random numbers to file
	ofstream file;
	file.open(filename);

	for (int i = 0; i < n; i++) {
		int x = next_number(range);
		file << to_string(x) + "\n";
	}
	file.close();
}

int main()
{
	//seed random number generator
	srand(int(time(NULL)));

	int n = 100000;
	int range = 32000;

	for (int i = 1; i < 4; i++) {		
		string filename = "input" + to_string(i) + ".txt";
		makefile(n, range, filename);
	}
	return 0;
}