//
// Created by Vova on 09.02.2021.
//

#pragma once

#include <geometry/polygon_area.h>
#include <geometry/polygon_perimeter.h>

/*

 3
1 1
1 4
7 4

 >>> 9.0

 _______________________________________________________________

 (3, 4),
 (5, 11),
 (12, 8),
 (9, 5),
 (5, 6)

 >>> 30.0

 */



inline void test_area_counting() {
	std::vector<point_i> polygon1 = {
			{1, 1},
			{1, 4},
			{7, 4},
	};


	std::vector<point_i> polygon2 = {
			{3, 4},
			{5, 11},
			{12, 8},
			{9, 5},
			{5, 6},
	};

	std::cout << "Area of polygon №1 is: " << count_polygon_area(polygon1) << std::endl;
	std::cout << "Area of polygon №2 is: " << count_polygon_area(polygon2) << std::endl;
}


inline void test_perimeter_counting() {
	std::vector<point_i> polygon1 = {
			{1, 1},
			{1, 4},
			{7, 4},
	};


	std::vector<point_i> polygon2 = {
			{3, 4},
			{5, 11},
			{12, 8},
			{9, 5},
			{5, 6},
	};

	std::cout << "Perimeter of polygon №1 is: " << count_polygon_perimeter(polygon1) << std::endl;
	std::cout << "Perimeter of polygon №2 is: " << count_polygon_perimeter(polygon2) << std::endl;
}

