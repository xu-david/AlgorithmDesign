// PartTwo.cpp
//Team Number: 1
//Team member: Junyi Zhou, Tianze Jiang
#include "utility.h" 
#include <queue>  
#include <list>
#include <vector>

class node {
public:
	node(char c, float w, node* left, node* right, string s) {
		content = c; 
		weight = w; 
		leftchild = left;
		rightchild = right;
		code = s; 
	}
	char content; //character of this node
	float weight; //frequence of this node
	node* leftchild;
	node* rightchild;
	string code; //Huffman code
};

// Insertion sort is adopted as our array is less than 128 in length
void insertion_sort(node** array, int start, int end) {
	for (int i = start + 1;i<end;i++) {
		node* tem = array[i];
		int j = i;
		while (j > start && array[j-1]->weight > tem->weight  ) {
			array[j] = array[j-1];
			j--;
		}
		array[j] = tem;
	}
}

// Generate Huffman tree
void huffman_tree(char* s, float* w, int n, node** array) {
	//generate all the nodes and sort them 
	for (int i = 0;i<n;i++) {
		array[i] = new node(s[i], w[i], NULL, NULL, "");
	}
	insertion_sort(array, 0, n);
	//combine the first two elements until there is only one element in the list
	int p = 0;
	while (p != n - 1) {
		node* min_1 = array[p];
		node* min_2 = array[p + 1];
		node* new_node = new node(0, min_1->weight + min_2->weight, min_1, min_2, "");
		array[p + 1] = new_node;
		p = p + 1;
		insertion_sort(array, p, n);
	}
}

// Accroding to tree, generate Huffman coding and return the nodelist
list<node*> huffman_code(node* p) {
	queue<node*> nq;
	list<node*> nodelist;
	nq.push(p);
	while (nq.size() != 0) {
		node* now = nq.front();
		nq.pop();
		node* l = now->leftchild;
		if (l != NULL) { l->code = now->code + "0"; nq.push(l); }
		node* r = now->rightchild;
		if (r != NULL) { r->code = now->code + "1"; nq.push(r); }
		if (l == NULL&&r == NULL) {
			nodelist.push_back(now);
		}
	}
	return nodelist;
}
//helper for STL list to sort by ASCii
bool compareASCii(node* a, node* b)
{
	if (a->content < b->content)
		return true;
	else
		return false;
}
//output the reslut file by nodelist
void outputList(string filename, list<node*> nodelist)
{
	ofstream output(filename);
	nodelist.sort(compareASCii);
	list<node*>::iterator current;
	//if there are "LF" or "space", output them in visual way
	for (current = nodelist.begin(); current != nodelist.end(); current++)
	{
		int temp = static_cast <int> ((*current)->content);
		if (temp == 10)
			output << "LF" << "\t" << (*current)->code << endl;
		else
		{
			if (temp == 32)
				output << "Space" << "\t" << (*current)->code << endl;
			else
			{
				output << (*current)->content << "\t" << (*current)->code << endl;
			}
		}
	}
	output.close();
}
// Read in Freq.txt, and output the Huffman dictionary
int main() {
	ifstream input("freq.txt"); // change the data file name here
	string line;
	vector<char> content;
	vector<float> freq;
	string character;
	int nfq;
	while (getline(input, line)) {
		stringstream ss(line);
		getline(ss, character, '\t');
		if (character == "LF")
			content.push_back(static_cast<char> (10));
		else if(character == "Space")
			content.push_back(static_cast<char> (32));
		else
		{
			if (character == "")
				content.push_back(static_cast<char> (32));
			else
			{
				const char *ctemp = character.c_str();
				content.push_back(ctemp[0]);
			}
		}
		ss >> nfq;
		freq.push_back(nfq);
	}
	input.close();
	node* array[46];
	char s[46];
	float w[46];
	//store imformation in s[] and w[]
	for (int i = 0; i < 46;i++) {
		w[i] = freq[i];
	}
	for (int i = 0; i < 46;i++) {
		s[i] = content.at(i);
	}
	//use s[] and w[] to generate the huffmantree
	huffman_tree(s, w, 46, array);
	list<node*> nodelist = huffman_code(array[45]);
	outputList("codetable.txt", nodelist);
	system("PAUSE");
}
