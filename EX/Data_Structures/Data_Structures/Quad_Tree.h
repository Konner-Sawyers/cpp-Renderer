#pragma once
#include <stdio.h>
#include <iostream>

class Quad_Tree
{

private:
	struct Node {

	};


	template<typename array_T, size_t array_rows, size_t array_columns>
	int max_value_x(array_T (&data_array)[array_rows][array_columns]) {
		int max = 0;

		for (int i = 0; i < 8; i++) {
			if (abs(data_array[i][0]) > abs(data_array[max][0])) {
				max = i;
			}
		}
		return abs(data_array[max][0]);
	};

	template<typename array_T, size_t array_rows, size_t array_columns>
	int max_value_y(array_T (&data_array)[array_rows][array_columns]) {
		int max = 0;

		for (int i = 0; i < 8; i++) {
			if (abs(data_array[i][1]) > abs(data_array[max][1])) {
				max = i;
			}
		}
		return abs(data_array[max][1]);
	};



public:


	float max_x, max_y;

	template<typename array_T, size_t array_rows, size_t array_columns>
	Quad_Tree(array_T (&data_array)[array_rows][array_columns]) {
		max_x = max_value_x(data_array);
		max_y = max_value_y(data_array);

		std::cout << max_x << ":" << max_y << std::endl;
	};
};

