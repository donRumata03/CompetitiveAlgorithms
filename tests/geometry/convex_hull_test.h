//
// Created by Vova on 09.02.2021.
//

#pragma once

#include <geometry/convex_hull.h>
#include <tests/geometry/test_data.h>




inline void test_convex_hull() {
	auto res = find_convex_hull(test_points);
	std::cout << res << std::endl;
}
