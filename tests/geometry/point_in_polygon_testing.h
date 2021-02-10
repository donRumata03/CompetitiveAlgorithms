//
// Created by Vova on 09.02.2021.
//

#pragma once


#include <geometry/point_in_polygon.h>

inline void test_point_in_polygon() {
	std::vector<point_i> non_convex_polygon = {
			{3, 4},
			{5, 11},
			{12, 8},
			{9, 5},
			{5, 6},
	};

	// point_i pnt = { 6, 5 };
	point_i pnt = { 4, 5 };

	std::cout << std::boolalpha << point_in_polygon(pnt, non_convex_polygon) << std::endl;
}



