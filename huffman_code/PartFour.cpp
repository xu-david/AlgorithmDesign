// PartFour.cpp
//Team Number: 2
#include "utility.h" 
#include <vector>

// Nodes for the decoding tree
class node {
public:
	node(char c, node* left, node* right, string s) {
		content = c;
		leftchild = left;
		rightchild = right;
		code = s;
	}
	char content; //character of this node
	node* leftchild;
	node* rightchild;
	string code; //Huffman code
};

// Generate tree
node* make_tree(vector<char> s, vector<string> c) {
	int n = c.size();
	// Make root
	node* head = new node(' ', nullptr, nullptr, "");

	// Start placing each code in the code table in the tree. For each character, traverse left for 0,
	// traverse right for 1, creating traversal nodes where necessary.
	for (int i = 0; i<n; i++) {
		node* cur = head;

		for (int j = 0; j < c[i].size() - 1; ++j) {
			if ((int)c[i].at(j) - (int)'0' == 0) {
				if (cur->leftchild == nullptr) {
					cur->leftchild = new node(' ', nullptr, nullptr, "");
				}
				cur = cur->leftchild;
			}
			else {
				if (cur->rightchild == nullptr) {
					cur->rightchild = new node(' ', nullptr, nullptr, "");
				}
				cur = cur->rightchild;
			}
		}
		if ((int)c[i].at(c[i].size() - 1) - (int)'0' == 0) {
			cur->leftchild = new node(s[i], nullptr, nullptr, c[i]);
		}
		else {
			cur->rightchild = new node(s[i], nullptr, nullptr, c[i]);
		}

	}

	return head;
}

string decode(node* tree, string coded) {
	string decoded;

	node* cur = tree;

	// Traverse the decode tree for each character. Left on 0, right on 1.
	// When tree hits a node, get character and reset tree to root
	for (char c : coded) {
		if ((int)c - (int)'0' == 0) {
			cur = cur->leftchild;
		}
		else {
			cur = cur->rightchild;
		}

		if (cur->leftchild == nullptr || cur->rightchild == nullptr) {
			decoded += cur->content;
			cur = tree;
		}
	}

	return decoded;
}

// Read the codetable and generate tree from codetable
node* generate_decode_tree(string filename) {
	vector<char> content;
	vector<string> codes;
	string character;
	string code;

	ifstream input(filename);
	string line;

	while (getline(input, line)) {
		stringstream ss(line);
		getline(ss, character, '\t');
		if (character == "LF")
			content.push_back(static_cast<char> (10));
		else if (character == "Space")
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
		ss >> code;
		codes.push_back(code);
	}
	input.close();

	return make_tree(content, codes);
}

// Generic read in file to string
string read_file(string filename) {
	ifstream input(filename);
	stringstream buffer;
	buffer << input.rdbuf();
	return buffer.str();
}

int main() {
	node* decode_tree = generate_decode_tree("codetable.txt");
	string coded = read_file("coded.txt");

	ofstream output("decoded.txt");
	output << decode(decode_tree, coded);

	return 0;
}
