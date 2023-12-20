#include <stdio.h>
#include <iostream>
#include "Quad_Tree.h"

int main() {
	std::cout << "Hello" << std::endl;

	/*
	int data_array[8][2] = {
		{6,5},
		{13,30},
		{17,3},
		{22,14},
		{9,7},
		{2,0},
		{16,5}
	};

	Quad_Tree myTree(data_array);
	*/

	int x = 54;
	int* p = &x;
	std::cout << *p;

	return 0;
}