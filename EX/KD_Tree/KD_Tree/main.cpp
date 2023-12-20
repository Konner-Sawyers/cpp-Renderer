#include <stdio.h>
#include <iostream>



class Binary_Tree {

public:
	int value;
	Binary_Tree *left, *right;



	Binary_Tree(int input) {
		value = input;
		left = NULL;
		right = NULL;
	}

	Binary_Tree* KD_Insert(int input, Binary_Tree* parent) {
		std::cout << "Parent Value " << parent << std::endl;
		if (parent == nullptr) {
			return new Binary_Tree(input);
		}

		else if (parent->value >= input) {
			std::cout << "Node already contains value " << parent->value << std::endl;
			std::cout << "Going left with " << input << std::endl;
			parent->left = KD_Insert(input, parent->left);
			return parent;
			
		}
		else if (parent->value < input) {
			std::cout << "Node already contains value " << parent->value << std::endl;
			std::cout << "Going right with " << input << std::endl;
			parent->right = KD_Insert(input, parent->right);
			return parent;
		}
		
	}

	

	void Print_Ascending(Binary_Tree* root) {
		if (root->left != nullptr) {
			Print_Ascending(root->left);
		}

		std::cout << root->value << std::endl;

		if (root->right != nullptr) {
			Print_Ascending(root->right);
		}

	}

};


int main() {

	int test_array[4] = { 5,2,7,1 };

	std::cout << "Init tree with 5 as root" << std::endl;

	Binary_Tree tree(5);

	tree.KD_Insert(2, &tree);
	tree.KD_Insert(7, &tree);
	tree.KD_Insert(1, &tree);
	tree.KD_Insert(8, &tree);
	tree.KD_Insert(6, &tree);
	tree.KD_Insert(4, &tree);

	tree.Print_Ascending(&tree);

};