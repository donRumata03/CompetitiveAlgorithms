//
// Created by Vova on 09.02.2021.
//

#pragma once


#include <geometry/geom_base.h>


template<class T>
double count_polygon_perimeter(const std::vector<base_point<T>>& polygon) {
	// View all the segments and sum their lengths:

	double perimeter = 0.;

	for (size_t i = 0; i < polygon.size(); ++i) {
		auto first_point = polygon[i];
		auto second_point = polygon[(i + 1) % polygon.size()];

		perimeter += std::sqrt(double(decltype(first_point)::sqr_dist(first_point, second_point)));
	}

	return perimeter;
}
