//
// Created by Vova on 09.02.2021.
//

#include "geometry_header.h"






///// ______________________					Main function			______________________:

int main() {

	li n;
	std::vector<base_point<li>> polygon;

	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		polygon.emplace_back();
		std::cin >> polygon.back().x >> polygon.back().y;
	}

	auto convex_hull = find_convex_hull(polygon);
	std::cout << convex_hull << std::endl;

	std::cout <<
	          count_polygon_perimeter(convex_hull) << std::endl <<
	          count_polygon_area(convex_hull) << std::endl;


	return 0;
}