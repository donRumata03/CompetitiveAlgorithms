//
// Created by Vova on 08.02.2021.
//

#pragma once

#include <geometry/polar_angle_sort.h>

inline void test_sorting_by_polar_angle() {

	point_i target_point = { 1, 1 };

	std::vector<point_i> test_points = {
			{1, 1},
			{4, 1},
			{5, 2},
			{5, 4},
			{2, 4},
			{1, 4},
			{1, 5},
			{0, 3},
			{0, 2},
			{-2, 2},
			{-1, 1},
			{-2, 1},
			{-3, 3},
			{-3, 0},
			{-1, 0},
			{-1, -1},
			{-3, -1},
			{-2, -3},
			{-0, -3},
			{1, -4},
			{2, -2},
			{3, -1},
			{6, -4}
	};
	std::shuffle(test_points.begin(), test_points.end(), std::mt19937{ std::random_device{}() });
	std::cout << "Before: " << test_points << std::endl;
	std::cout << "___________________________________" << std::endl;

	auto res = sort_by_polar_angle(target_point, test_points);
	std::cout << "After: " << res << std::endl;

}
