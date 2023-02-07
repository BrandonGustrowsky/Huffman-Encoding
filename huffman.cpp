// Developer: Brandon Gustrowsky
// Assignment Number: 4
// Assignment: Huffman Coding Tree
// Date Last Modified: October 19, 2022
// Honor Statement: I have neither given nor received any unauthorized help on this assignment.

// -------------------- Code --------------------

#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
#include "tree_printer.hpp"

using namespace std;

//@param char letter : The letter of the alphabet the node is storing
//@param double freq : The number of times the letter appears in the document
// @property Node *left  : The left child node
//@property Node *right : The right child node
struct Node {
    
    Node *left;
    Node *right;
    char letter;
    double freq;

    Node(char letter, double freq) {
        this->letter = letter;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        delete this->left;
        delete this->right;
    }
};

struct Compare {
    bool operator()(const Node* a, const Node* b) {
        return a->freq > b->freq;
    }
};

map<char, int> frequencies = {
    {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0},
    {'E', 0}, {'F', 0}, {'G', 0}, {'H', 0},
    {'I', 0}, {'J', 0}, {'K', 0}, {'L', 0},
    {'M', 0}, {'N', 0}, {'O', 0}, {'P', 0},
    {'Q', 0}, {'R', 0}, {'S', 0}, {'T', 0},
    {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0},
    {'Y', 0}, {'Z', 0}
};

map<char, string> bitstrings = {
    {'A', ""}, {'B', ""}, {'C', ""}, {'D', ""},
    {'E', ""}, {'F', ""}, {'G', ""}, {'H', ""},
    {'I', ""}, {'J', ""}, {'K', ""}, {'L', ""},
    {'M', ""}, {'N', ""}, {'O', ""}, {'P', ""},
    {'Q', ""}, {'R', ""}, {'S', ""}, {'T', ""},
    {'U', ""}, {'V', ""}, {'W', ""}, {'X', ""},
    {'Y', ""}, {'Z', ""}
};

int frequencies_size = frequencies.size();

//Counts the number of times each character appears after the input has been filtered.
// @param string input : The filtered user input.
void countCharacters(string input) {
    for (auto& [key, val] : frequencies) {
        int count = 0;
        for (char letter : input) {
            if (letter == key) {
                count++;
            }
        val = count;
        }
    }
}

// Builds the huffman tree by creating nodes and properly connecting them.
//@param priority_queue<Node*, vector<Node*>, Compare> pq : The vector all the nodes are stored in.
Node* build_huffman_tree(priority_queue<Node*, vector<Node*>, Compare> pq) {
    int length = pq.size();
    while (length > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node* treeNode = new Node('\0', left->freq + right->freq);
        treeNode->left = left;
        treeNode->right = right;
        pq.push(treeNode);
        length--;
    }
    return pq.top();
}

//Traverses the tree by node-left subtree-right subtree to build each character's bitstrings.
// @param Node *root : The root node of the tree
// @param string direction : The direction the function is traversing, options are 'left' or 'right'.
// @param string bit : The bit string representing each letter.
int preOrderTraversal(Node *root, string direction, string bit) {
    if (root == nullptr) {
        return 0;
    }

    if (direction == "left") {
        bit += "0";
    } else if (direction == "right") {
        bit += "1";
    }

    if (root->letter) {
        bitstrings[root->letter] = bit;
    }

    preOrderTraversal(root->left, "left", bit);
    preOrderTraversal(root->right, "right", bit);
    return 0;
}

int main() {
    // Get the input, format it, and print the result
    string filteredInput;
    
    //Remove any nonalpha characters and capitalize all remaining characters.
    char character;
    while (cin.get(character)) {
        if (isalpha(character)) {
            filteredInput += toupper(character);
        }
    }
    cout << filteredInput << endl;

    int adjustedLength = filteredInput.size();

    //Count the number of times each character appears and print the result
    countCharacters(filteredInput);

    cout << endl << "Counts:" << endl << "-------" << endl;

    // Create priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;
    int pqSize = pq.size();
    
    vector<double> adjustedFrequencies{};

    // print out the letter frequencies and add them to the priority queue
    for (auto& [key, value] : frequencies) {
        cout << key << ": " << value << endl;
        Node *created = new Node(key, (double)value/(double)adjustedLength);
        adjustedFrequencies.push_back((double)value/(double)adjustedLength);
        pq.push(created);
    }

    //Delete all the nodes in the pq vector
    for (int i=0; i<pqSize; i++) {
        Node *node = pq.top();
        pq.pop();
        delete node;

    }
    cout << "Total = " << adjustedLength << endl;
    cout <<"---------------------------------" << endl << endl <<endl;

    // Build the huffman tree
    Node *root = build_huffman_tree(pq);

    Trunk* trunk = new Trunk(nullptr, "      ");
    print_tree(root, nullptr, false);

    cout << "---------------------------------" << endl << endl;

    // Traverse through the tree and build the bitstrings
    preOrderTraversal(root, "", "");

    // Print the bitstrings A-Z
    for (auto& [key, value] : bitstrings) {
        cout << key << ": " << value << endl; 
    }

    // Calculate and print the fixed encoding and huffman encoding sizes
    int mapSize = frequencies.size();
    int huffmanLength = 0;
    for (char i = 'A'; i <= 'Z'; i++) {
        huffmanLength += frequencies[i] * bitstrings[i].length();
    };

    cout << endl << "  Fixed encoding: " << adjustedLength * 5 << " bits" << endl;
    cout << "Huffman encoding: " << huffmanLength << " bits" << endl;

    // Delete the tree
    delete root;
}
