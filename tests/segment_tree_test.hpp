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

inline void stree_sum_test_base(const std::vector<li>& test_vector, const std::vector<std::pair<li, li>>& test_cases) {
	SumSegmentTree<li> tree(test_vector);

	for (auto& test_case : test_cases) {
		li answer = tree.sum(test_case.first, test_case.second);
		li right_answer = std::accumulate(test_vector.begin() + test_case.first, test_vector.begin() + test_case.second, 0LL);

		std::cout << test_case << " : "
		          << answer <<
		          " (expected: " <<
		          right_answer
		          << ") => " << (answer == right_answer ? "RIGHT" : "WRONG")
		          << std::endl;
	}
}

inline void stree_sum_test8()
{
	std::vector<li> test_vector_pow_of_2 = {
			1, 2, 3, 4, 5, 6, 7, 8 // 8 elements
	};


	std::vector<std::pair<li, li>> test_tasks = {
			{ 0, test_vector_pow_of_2.size() },
			{ 0, 1 },
			{ 0, 2 },
			{ 0, 3 },
			{ 0, 4 },
			{ 0, 5 },
			{ 0, 6 },
			{ 0, 7 },
			{ 0, 8 },

			{ 1, 1 },
			{ 1, 2 },
			{ 1, 3 },
			{ 1, 4 },
			{ 1, 5 },
			{ 1, 7 },
			{ 1, 8 },


			{ 5, 7 },
	};

	stree_sum_test_base(test_vector_pow_of_2, test_tasks);
}

inline void stree_sum_test3()
{
	std::vector<li> test_vector = {
			1, 2, 3 // 3 elements
	};


	std::vector<std::pair<li, li>> test_tasks = {
			{ 0, test_vector.size() },
			{ 0, 1 },
			{ 0, 2 },
			{ 0, 3 },

			{ 1, 1 },
			{ 1, 2 },
			{ 1, 3 },

			{ 2, 3 },
			{ 2, 2 },
			{ 1, 1 },
	};

	stree_sum_test_base(test_vector, test_tasks);
}
////////////////////////////////////////////////////////


inline void stree_getting_test_base(const std::vector<li>& test_vector)
{
	SumSegmentTree<li> tree(test_vector);

	for (li i = 0; i < test_vector.size(); i++) {
		std::cout << i << " : " << tree.get(i) << " (expected: " << test_vector[i] << ") => "
		          << (test_vector[i] == tree.get(i) ? "RIGHT" : "WRONG") << std::endl;
	}
}

inline void stree_getting_test8() {
	std::vector<li> test_vector = {
			1, 2, 3, 4, 5, 6, 7, 8 // 8 elements
	};

	stree_getting_test_base(test_vector);
}


inline void stree_getting_test3() {
	std::vector<li> test_vector = {
			1, 2, 3 // 3 elements
	};

	stree_getting_test_base(test_vector);
}
