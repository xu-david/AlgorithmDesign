#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int find_peak(vector<int> heights, int start, int end) {
	//recursively find the peak in the array

	int mid = (start + end) / 2;
	//printf("Start %i; Mid %i, End %i\n", start, mid, end);
	//system("pause");

	//base case, peak somewhere between A[2...n-1]
	if (heights[mid] > heights[mid - 1] && heights[mid] > heights[mid + 1]) {
		return mid;
	}

	//base case, peak at A[1]
	else if(start == 0 && heights[start] > heights[start + 1]) {
		return start;
	}

	//base case, peak at A[n]
	else if (end == heights.size() - 1 && heights[end - 1] > heights[end - 2]) {
		return end;
	}

	//peak somewhere between A[i+1 ... n]
	else if (heights[mid] < heights[mid - 1]) {
		return find_peak(heights, start, mid - 1);
	}

	//peak somewhere between A[1 ... i-1]
	else if (heights[mid] < heights[mid + 1]) {
		return find_peak(heights, mid + 1, end);
	}

	else {
		throw invalid_argument("Error in input file. Integers must be distinct.");
	}
}

int main()
{
	vector<int> heights;

	//read input file into vector
	ifstream inputfile("peak.txt");
	if (inputfile) {
		int value;
		while (inputfile >> value) {
			heights.push_back(value);
		}
	}

	//start divide and conquer recursion
	int peak = find_peak(heights, 0, heights.size() - 1);

	printf("The peak is found at index %i with height %i.\n", peak, heights[peak]);
	system("pause");
	return 0;
}