//
// Created by Vova on 09.02.2021.
//

#pragma once

#include <geometry/geom_base.h>


template<class T>
double count_polygon_area(const std::vector<base_point<T>>& polygon) {
	// View all the segments and sum the trapeziums' oriented areas:

	double area = 0.;

	for (size_t i = 0; i < polygon.size(); ++i) {
		auto first_point = polygon[i];
		auto second_point = polygon[(i + 1) % polygon.size()];

		area += (first_point.y + second_point.y) * (second_point.x - first_point.x) * 0.5;
	}

	return std::abs(area);
}