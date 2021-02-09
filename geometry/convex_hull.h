//
// Created by Vova on 08.02.2021.
//

#pragma once


#include <geometry/geom_base.h>
#include <geometry/polar_angle_sort.h>

/// Helpers:


template<class T>
void pop_second(std::vector<base_point<T>>& stack) {
	auto top = stack.pop_back();
	stack.pop_back();
	stack.push_back(top);
}


template<class T>
void add_point_to_convex_hull_with_reduction(base_point<T> target_point, std::vector<base_point<T>>& convex_hull, base_point<T> new_point) {
	// Push:
	convex_hull.push_back(new_point);


	// Make reduction:
	while (convex_hull.size() >= 3) {
		// TODO: add points on one line or not? Try both!

		auto top = convex_hull.back();
		auto middle = convex_hull[convex_hull.size() - 2];
		auto old = convex_hull[convex_hull.size() - 3];

		point_i to_next = top - middle;
		point_i to_prev = old - middle;

		// If they are parallel:
		if (are_parallel(to_next, to_prev)) {
			// Take the furthest of them!
			// Dist from first_point!!!!!!!!!!!!!
			if (base_point<T>::sqr_dist(target_point, middle) > base_point<T>::sqr_dist(target_point, top)) {
				// If middle point is further, delete top:
				convex_hull.pop_back();
			}
			else { // If top point is further, delete second:
				pop_second(convex_hull);
			}
		}
		else {
			// Delete middle point or not?
			// Rotation should be clockwise ==> cross product should be more than zero:
			if (cross_product(to_prev, to_next) > 0) {
				// DELETE (leave top one but delete second)
				pop_second(convex_hull);
			}
			else {
				// Stop deletion:
				break;
			}
		}

		// auto top = convex_hull.pop_back();
		// convex_hull.pop_back();
		// convex_hull.push_back(top);
	}

}


template<class T>
std::vector<base_point<T>> find_convex_hull(const std::vector<base_point<T>>& points) {
	/// Select the point in the bottom:

	// auto first_point = points[0];
	li first_point_index = 0;

	li point_index = 0;
	for (auto& point : points) {
		if (point.y < points[first_point_index].y) {
			first_point_index = point_index;
		}
		point_index++;
	}

	std::vector<base_point<T>> other_points;
	other_points.reserve(points.size() - 1);
	for (size_t i = 0; i < points.size(); ++i) {
		if(i != first_point_index) other_points.push_back(points[i]);
	}
	auto first_point = points[first_point_index];

	/// Perform polar angle sorting:
	auto other_sorted = sort_by_polar_angle(first_point, other_points);

	/// Delete bad points from the convex hull:
	std::vector<base_point<T>> convex_hull { first_point };

	/// There should be clockwise turn everywhere:
	for (auto& other_point : other_points) {
		add_point_to_convex_hull_with_reduction(first_point, convex_hull, other_point);
	}
	add_point_to_convex_hull_with_reduction(convex_hull, first_point);
	convex_hull.pop_back();

	return convex_hull;
}