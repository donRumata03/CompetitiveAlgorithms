//
// Created by Vova on 09.02.2021.
//

#pragma once

#include <geometry/geom_base.h>


inline void are_parallel_test() {
	std::cout << std::boolalpha;

	std::cout << are_parallel(point_d{1.5, 2}, {4.5, 6}) << std::endl;
	std::cout << are_parallel(point_d{-1.5, -2}, {4.5, 6}) << std::endl;
	std::cout << are_parallel(point_d{1.5, 2}, {4.5, 7}) << std::endl;
}


inline void are_co_directed_test() {
	std::cout << std::boolalpha;

	std::cout << are_co_directed(point_d{1.5, 2}, {4.5, 6}) << std::endl;
	std::cout << are_co_directed(point_d{-1.5, -2}, {4.5, 6}) << std::endl;
	std::cout << are_co_directed(point_d{1.5, 2}, {4.5, 7}) << std::endl;
}


inline void point_on_line_test() {
	std::cout << std::boolalpha;

	std::cout << point_on_line(point_d{3.5, 2.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_line(point_d{7, 5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_line(point_d{0, 0}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;

	std::cout << point_on_line(point_d{5, 3.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
}


inline void point_on_segment_test() {
	std::cout << std::boolalpha;

	// True:
	std::cout << point_in_segment(point_d{3.5, 2.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{-3.5, -2.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{-3.5 / 3, -2.5 / 3}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{0, 0}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;

	std::cout << "____________________________________________" << std::endl;

	// On line but not on segment:
	std::cout << point_in_segment(point_d{7, 5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{-3.5 * 101, -2.5 * 101}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;


	// Not even on line:
	std::cout << point_in_segment(point_d{5, 3.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{2, 3.}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_in_segment(point_d{-6, -2}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
}

inline void test_on_ray() {
	std::cout << std::boolalpha;

	// True:
	std::cout << point_on_ray(point_d{3.5, 2.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{-3.5, -2.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{-3.5 / 3, -2.5 / 3}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{0, 0}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{7, 5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;

	std::cout << "____________________________________________" << std::endl;

	// On line but not on ray:
	std::cout << point_on_ray(point_d{-3.5 * 101, -2.5 * 101}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{-3.5 * 141, -2.5 * 141}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;


	// Not even on line:
	std::cout << point_on_ray(point_d{5, 3.5}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{2, 3.}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
	std::cout << point_on_ray(point_d{-6, -2}, {-3.5, -2.5}, {3.5, 2.5}) << std::endl;
}