//
// Created by Vova on 09.02.2021.
//

#include "geometry_header.h"


///// ______________________					Main function			______________________:

int main() {

	li n;
	std::vector<base_point<double>> polygon;

	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		polygon.emplace_back();
		std::cin >> polygon.back().x >> polygon.back().y;
	}
	std::cout << count_polygon_area(polygon) << std::endl;

	return 0;
}
