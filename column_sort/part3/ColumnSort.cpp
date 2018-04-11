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
	//heap sort from book using 0 index heap instead of 1 index heap
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

bool SortCheck(vector<vector<short>>& A, int n, int r) {
	//check if values are in sorted order
	// true -> array is sorted
	// false -> array is not sorted
	for (int x = 0; x < n - 1; x++) {
		int i = A[x / r][x % r];
		int y = x + 1;
		int j = A[y / r][y % r];
		if (i > j) {
			cout << "invalid " << x << " " << i << " " << j << endl;
			return false;
		}
	}
	return true;
}

void print_cs(vector<vector<short>>& A, int n, int r) {
	//walks through columns and writes values
	for (int x = 0; x < n ; x++) {
		cout << x << " " << x % r << " " << x / r << " " << A[x / r][x % r] << endl;
	}
	system("pause");
}

void sort_columns(vector<vector<short>>& A, int s) {
	//individually sort a column
	for (int i = 0; i < s; i++) {
		HeapSort(A[i]);
	}
}

void ColumnSort(vector<vector<short>>& A, int r, int s) {
	//print_cs(A, r*s, r);

	//1. sort s columns of r elements
	sort_columns(A, s);
	//print_cs(A, r*s, r);

	//2. Transpose
	vector<short> tmp;
	for (int i = 0; i < r * s; i++) {
		tmp.push_back(A[i / r][i % r]);
	}

	for (int i = 0; i < r * s; i++) {
		A[i % s][i / s] = tmp[i];
	}
	tmp.clear();

	//print_cs(A, r*s, r);

	//3. sort s columns of r elements
	sort_columns(A, s);
	//print_cs(A, r*s, r);
	
	//4. Untranspose
	for (int i = 0; i < r * s; i++) {
		tmp.push_back(A[i % s][i / s]);
	}
	for (int i = 0; i < r * s; i++) {
		A[i / r][i % r] = tmp[i];
	}
	tmp.clear();
	//print_cs(A, r*s, r);

	//5. Resort again like step 1
	sort_columns(A, s);
	//print_cs(A, r*s, r);

	//6. Shift by r/2 from back to front
	for (int i = r * s - 1; i >= 0; i--) {
		int j = i + r / 2;
		A[j / r][j % r] = A[i / r][i % r];
	}
	//print_cs(A, r*s+r, r);

	//fill with sentinel values at front and back
	for (int i = 0; i < r / 2; i++) {
		A[0][i] = -32766;
	}
	for (int i = r / 2; i < r; i++) {
		A[s][i] = 32767;
	}
	//print_cs(A, r*s+r, r);

	//7. Resort
	sort_columns(A, s);
	//print_cs(A, r*s+r, r);

	//8. Shift back by r/2 from front to back
	for (int i = 0; i < s * r; i++) {
		int j = i + r / 2;
		A[i / r][i % r] = A[j / r][j % r];
		}
	//print_cs(A, r*s, r);
}

int main() {
	//input file name
	string inputfile = "Part1Data.txt";
	const int n = 100000;
	const int r = 5000;
	const int s = 20; //r * s = n; r % s = 0; r >= 2(s-1)^2 = 722

	//read file into r rows x s col matrix; initialize s+1 instead of s
	vector<vector<short>> A(s + 1, vector<short>(r));
	ifstream file(inputfile);
	if (file) {
		short value;
		int i = 0;
		while (file >> value) {
			A[i / r][i % r] = value;
			i++;
		}
	}

	//timer
	Timer t = Timer();
	ColumnSort(A, r, s);
	double elapsed = t.elapsed_time();

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout << "elapsed time: " << elapsed << endl;

	//check if array is sorted
	bool check_sorted = SortCheck(A, n, r);
	if (check_sorted == false) {
		throw invalid_argument("array not sorted properly");
	}

	//write output file
	string outputfile = "Results.txt";
	ofstream ofile(outputfile);
	if (ofile.is_open()) {
		for (int i = 0; i < n; i++) {
			ofile << A[i / r][i % r] << endl;
		}
		ofile.close();
	}

	system("pause");
	return 0;
}