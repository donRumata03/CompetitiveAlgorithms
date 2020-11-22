//
// Created by Vova on 22.11.2020.
//

#pragma once

#include "data_structures/segment_tree.hpp"

inline void stree_building_test() {
	std::vector<li> test_vector_pow_of_2 = {
		// 1, 2, 3, 4, 5, 6, 8, 10 // 8 elements
		1, 2, 3, 4, 5, 6, 7, 8 // 8 elements
	};


	SumSegmentTree<li> tree(test_vector_pow_of_2);


}

