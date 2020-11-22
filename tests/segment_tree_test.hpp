//
// Created by Vova on 22.11.2020.
//

#pragma once

#include "data_structures/segment_tree.hpp"

inline void stree_building_test() {
	std::vector<li> test_vector_not_pow_of_2 = {
		1, 2, 3, // 3 elements
	};
	std::cout << "Total sum is: " << std::accumulate(test_vector_not_pow_of_2.begin(), test_vector_not_pow_of_2.end(), 0LL) << std::endl;

	SumSegmentTree<li> first_tree(test_vector_not_pow_of_2);

	// return;

	std::cout << "___________________________________" << std::endl;

	std::vector<li> test_vector_pow_of_2 = {
		// 1, 2, 3, 4, 5, 6, 8, 10 // 8 elements
		1, 2, 3, 4, 5, 6, 7, 8 // 8 elements
	};
	std::cout << "Total sum is: " << std::accumulate(test_vector_pow_of_2.begin(), test_vector_pow_of_2.end(), 0LL) << std::endl;

	SumSegmentTree<li> tree(test_vector_pow_of_2);


}

