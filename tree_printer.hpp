// Developer: Brandon Gustrowsky
// Assignment Number: 4
// Assignment: Huffman Coding Tree
// Date Last Modified: October 19, 2022
// Honor Statement: I have neither given nor received any unauthorized help on this assignment.

// -------------------- Code --------------------

#pragma once
#include <iostream>

// Adapted from 
// https://www.techiedelight.com/c-program-print-binary-tree/

const std::string HORIZONTAL_LINE = "--";
const std::string VERTICAL_LINE = "|";
const std::string RIGHT_BRANCH = ".--";
const std::string LEFT_BRANCH  = "`--";
const std::string CONNECTOR    = "     |";


struct Trunk {
    Trunk *prev;
    std::string str;
 
    Trunk(Trunk *prev, std::string str) {
        this->prev = prev;
        this->str = str;
    }

    ~Trunk() {
        delete this->prev;
    }
};
 
// Helper function to print branches of the binary tree
void show_trunks(Trunk *p) {
    if (p) {
        show_trunks(p->prev);
        std::cout << p->str;
        // std::cout << "p->str ==> " << p->str << std::endl;
    }
}


// Type T must be a pointer to a struct or class
// with a printable public member named data and 
// public members named  left and right that have 
// same type as T.
// You may need to adapt the code here based on the
// specifics of your tree node type.
template <typename T>
void print_tree(T root, Trunk *prev, bool is_left) {
    if (root) {
        std::string prev_str = "      ";
        Trunk *trunk = new Trunk(prev, prev_str);
        print_tree(root->right, trunk, true);
        if (!prev) {
            trunk->str = HORIZONTAL_LINE;
        } else if (is_left) {
            trunk->str = RIGHT_BRANCH;
            prev_str = CONNECTOR;
        } else {
            trunk->str = LEFT_BRANCH;
            prev->str = prev_str;
        }
        show_trunks(trunk);
        if (root->letter) {
            std::cout << "[" << root->letter << ":" << root->freq << "]" << std::endl;
        } else {
            std::cout << "(" << root->freq << ")" << std::endl;
        }
        // }
        // std::cout << " " << root->freq << '\n';
        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = CONNECTOR;
        print_tree(root->left, trunk, false);
    }
}
