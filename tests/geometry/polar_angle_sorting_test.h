//
// Created by Vova on 08.02.2021.
//

#pragma once

#include <geometry/polar_angle_sort.h>
#include <tests/geometry/test_data.h>


inline void test_sorting_by_polar_angle() {

	// point_i target_point = { 1, 1 };
	point_i target_point = { 1, -4 };

	auto local_test_points = test_points;

	std::shuffle(local_test_points.begin(), local_test_points.end(), std::mt19937{ std::random_device{}() });
	std::cout << "Before: " << local_test_points << std::endl;
	std::cout << "___________________________________" << std::endl;

	auto res = sort_by_polar_angle(target_point, local_test_points);
	std::cout << "After: " << res << std::endl;

}
