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
		li answer = tree.compute(test_case.first, test_case.second);
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

inline void stree_setting_test_base(const std::vector<li>& test_vector, const std::vector<std::pair<li, li>>& queries)
{
	auto non_const_vector = test_vector;

	SumSegmentTree<li> tree(test_vector);

	li sum = std::accumulate(test_vector.begin(), test_vector.end(), 0LL);

	for (auto& query : queries) {
		sum += query.second - non_const_vector[query.first];

		non_const_vector[query.first] = query.second;
		tree.set(query.first, query.second);


		std::cout << "tree.get(" << query.first << ") = " << tree.get(query.first) << " (expected: " << non_const_vector[query.first] << ") => "
		<< (non_const_vector[query.first] == tree.get(query.first) ? "RIGHT" : "WRONG") << std::endl;

		std::cout << "sum is: " << tree.compute(0, test_vector.size()) << ", expected: " << sum << std::endl;
	}
}

inline void stree_setting_test3() {
	std::vector<li> test_vector = {
			1, 2, 3 // 3 elements
	};

	std::vector<std::pair<li, li>> queries = {
			{ 1, 1 },
			{ 2, 10 },
			{ 1, 7 },
			{ 0, 3 }
	};


	stree_setting_test_base(test_vector, queries);
}

//////////////////////////////////////////////////////////////
///// 						Min trees				//////////
//////////////////////////////////////////////////////////////


inline void test_min_and_max_stree() {
	std::vector<li> test_vector = {
		1, 2, 3, 4, 5, 6, 7
	};

	std::vector<std::tuple<bool, li, li>> requests = {
		// False for set, True for compute

			{ true, 0, 2 },
			{  }
	};

	MinSegmentTree<li> min_tree(test_vector);
	MaxSegmentTree<li> max_tree(test_vector);

	for (auto& query : requests) {
		if (std::get<0>(query)) {
			std::cout << "Max [" << std::get<1>(query) << "; " << std::get<2>(query) << ") is " <<
		}
	}
}
