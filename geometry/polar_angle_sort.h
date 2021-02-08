//
// Created by Vova on 08.02.2021.
//

#pragma once

#include "geom_base.h"


/// 											Selection:


template<class T>
std::vector<base_point<T>> select_same_points(const std::vector<base_point<T>>& points, base_point<T> target_point) {
	std::vector<base_point<T>> res;
	std::copy_if(points.begin(), points.end(), std::back_inserter(res), [&target_point](base_point<T> point){ return point == target_point; });
	return res;
}


template<class T>
std::vector<base_point<T>> select_right_ray(const std::vector<base_point<T>>& points, base_point<T> target_point) {
	std::vector<base_point<T>> res;
	std::copy_if(points.begin(), points.end(), std::back_inserter(res), [&target_point](base_point<T> point){
		return point.y == target_point.y and point.x > target_point.x;
	});
	return res;
}



template<class T>
std::vector<base_point<T>> select_left_ray(const std::vector<base_point<T>>& points, base_point<T> target_point) {
	std::vector<base_point<T>> res;
	std::copy_if(points.begin(), points.end(), std::back_inserter(res), [&target_point](base_point<T> point){
		return point.y == target_point.y and point.x < target_point.x;
	});
	return res;
}



template<class T>
std::vector<base_point<T>> select_upper_half(const std::vector<base_point<T>>& points, base_point<T> target_point) {
	std::vector<base_point<T>> res;
	std::copy_if(points.begin(), points.end(), std::back_inserter(res), [&target_point](base_point<T> point){
		return point.y > target_point.y;
	});
	return res;
}


template<class T>
std::vector<base_point<T>> select_bottom_half(const std::vector<base_point<T>>& points, base_point<T> target_point) {
	std::vector<base_point<T>> res;
	std::copy_if(points.begin(), points.end(), std::back_inserter(res), [&target_point](base_point<T> point){
		return point.y < target_point.y;
	});
	return res;
}


/// 											Sorting:


template<class T>
std::vector<base_point<T>> sort_by_cotangent(std::vector<base_point<T>>& points, base_point<T> target_point, bool reverse = false) {
	auto get_cotangent = [&target_point](base_point<T> point){
		return double(point.x - target_point.x) / double(point.y - target_point.y);
	};

	std::sort(points.begin(), points.end(), [&reverse, &get_cotangent](base_point<T> first, base_point<T> second){
		if (not reverse) {
			return get_cotangent(first) < get_cotangent(second);
		}
		else {
			return get_cotangent(first) > get_cotangent(second);
		}
	});

	return points;
}


/**
 * Use this order:
 *	1) Points identical to the «target» one and with the same y with bigger x
 *	2) First quarter
 *	3) Points with the same x and with y > y of target point
 *	4) Second Quarter
 *	5) Same y, smaller x
 *	6) Third quarter
 *	7) Same x, smaller y
 *	8) Fourth quarter
 *
 */
template<class T>
std::vector<base_point<T>> sort_by_polar_angle(base_point<T> target_point, const std::vector<base_point<T>>& points) {
	// Split the points into:
	//  1. The same ones
	//  2. Ray to right
	//  3. Upper ones
	//  4. Ray to left
	//  5. Bottom ones

	auto same_points = select_same_points(points, target_point);

	auto right_ray_points = select_right_ray(points, target_point);
	auto left_ray_points = select_left_ray(points, target_point);

	auto upper_half = select_upper_half(points, target_point);
	auto bottom_half = select_bottom_half(points, target_point);

	auto sorted_upper_half = sort_by_cotangent(upper_half, target_point, true);
	auto sorted_bottom_half = sort_by_cotangent(bottom_half, target_point, true);

	std::vector<base_point<T>> res;
	li total_size = same_points.size() +
					right_ray_points.size() + left_ray_points.size() +
					sorted_upper_half.size() + sorted_bottom_half.size();
	assert(total_size == points.size());
	res.resize(total_size);

	auto after_sames = std::copy(same_points.begin(), same_points.end(), res.begin());

	auto after_right_ray = std::copy(right_ray_points.begin(), right_ray_points.end(), after_sames);
	auto after_upper_half = std::copy(sorted_upper_half.begin(), sorted_upper_half.end(), after_right_ray);

	auto after_left_ray = std::copy(left_ray_points.begin(), left_ray_points.end(), after_upper_half);
	auto after_bottom_half = std::copy(sorted_bottom_half.begin(), sorted_bottom_half.end(), after_left_ray);
	assert(after_bottom_half == res.end());

	return res;
}
