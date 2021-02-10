//
// Created by Vova on 09.02.2021.
//


#include "geometry_header.h"




int main() {

	li n;
	point_d point;
	std::vector<base_point<double>> polygon;

	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		polygon.emplace_back();
		std::cin >> polygon.back().x >> polygon.back().y;
	}
	std::cin >> point.x >> point.y;

	// if (point_in_polygon(point, polygon)) {
	if (point_in_convex_polygon(point, polygon)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}

	return 0;
}
