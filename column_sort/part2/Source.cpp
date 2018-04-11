#include "utility.h"

Timer::Timer()
	//constructor - turns on the timer
{
	start_time = clock();
}

double Timer::elapsed_time()
	//compute elapsed time between start and stop
{
	clock_t end_time = clock();

	return ((double)(end_time - start_time)) / ((double)CLOCKS_PER_SEC);
}

void Timer::reset()
	//restarts the timer
{
	start_time = clock();
}

void max_heapify(vector<short>& A, int n, int i) {
	//heap sort using 0 index heap instead of 1 index heap
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest = i;

	if (l < n && A[l] > A[i]) {
		largest = l;
	}
	if (r < n && A[r] > A[largest]) {
		largest = r;
	}
	if (largest != i) {
		swap(A[i], A[largest]);
		max_heapify(A, n, largest);
	}
}

void HeapSort(vector<short>& A) {
	//build max heap
	int n = A.size();
	for (int i = n / 2 - 1; i >= 0; i--) {
		max_heapify(A, n, i);
	}

	//lower heap size by 1 and reheap
	for (int i = n - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		max_heapify(A, i, 0);
	}
}

bool SortCheck(vector<short>& A) {
	//check if values are in sorted order
	// true -> array is sorted
	// false -> array is not sorted
	int n = A.size() - 1;
	for (int i = 0; i < n; i++) {
		if (A[i] > A[i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	//input file name
	string inputfile = "Part1Data.txt";

	//read file
	vector<short> A;

	ifstream file(inputfile);
	if (file) {
		short value;
		while (file >> value) {
			A.push_back(value);
		}
	}

	//timer
	Timer t = Timer();
	HeapSort(A);
	double elapsed = t.elapsed_time();

	
	//check if array is sorted
	bool check_sorted = SortCheck(A);
	if (check_sorted == false) {
		throw invalid_argument("array not sorted properly");
	}

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout << "elapsed time " << elapsed << "\n";

	system("pause");
	return 0;
}