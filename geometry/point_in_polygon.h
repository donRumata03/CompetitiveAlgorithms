//
// Created by Vova on 08.02.2021.
//

#pragma once


#include "geom_base.h"
#include "polar_angle_sort.h"

point_i get_safe_ray_point(point_i point, const std::vector<point_i>& polygon) {
	assert(polygon.size() >= 2);

	auto polar_angle_sorted = sort_by_polar_angle(point, polygon);
	auto first_point = polar_angle_sorted[0];
	auto second_point = polar_angle_sorted[1];

	for (auto candidate_second_point : polygon) {
		if (candidate_second_point.y != first_point.y) {
			second_point = candidate_second_point;
			break;
		}
	}

	return first_point + second_point - point;
}


inline bool point_in_polygon(point_i point, const std::vector<point_i>& polygon) {
	point_i generated_point = get_safe_ray_point(point, polygon);

	li intersections = 0;

	for (size_t i = 0; i < polygon.size(); ++i) {
		auto this_point = polygon[i];
		auto next_point = polygon[(i + 1) % polygon.size()];

		if (ray_intersects_segment(point, generated_point, this_point, next_point)) {
			intersections++;
		}
	}

	return bool(intersections % 2);
}
