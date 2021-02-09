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
