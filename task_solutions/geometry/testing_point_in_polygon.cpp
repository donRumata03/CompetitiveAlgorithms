//
// Created by Vova on 08.02.2021.
//

/**
 * Checking if the given point is in the polygon (which is not necessary convex)
 * https://informatics.mccme.ru/mod/statements/view.php?id=1160&chapterid=288#1
 */


/// ______________________					Olymp functions:		______________________

//
// Created by Vova on 22.11.2020.
//


#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <cassert>
#include <utility>
#include <fstream>

#include <unordered_set>
#include <unordered_map>

#include <optional>
#include <ciso646>


using li = long long int;


template<class FirstT, class SecondT>
std::ostream& operator << (std::ostream& os, const std::pair<FirstT, SecondT>& pair) {
	os << "(" << pair.first << ", " << pair.second << ")";

	return os;
}


template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vector) {
	// for (auto& v: vector) os << v << " ";
	for (size_t i = 0; i < vector.size(); ++i) {
		os << vector[i];
		if (i != vector.size() - 1) os << " ";
	}

	return os;
}



/// ______________________					Geom base:		______________________


constexpr double geometry_epsilon = 1e-10;


template<class T = li>
struct base_point {
	T x {};
	T y {};

	base_point(T _x, T _y) { x = _x; y = _y; }

	friend base_point<T> operator- (base_point<T> p1, base_point<T> p2) {
		return base_point<T>{ p1.x - p2.x, p1.y - p2.y };
	}

	friend base_point<T> operator+ (base_point<T> p1, base_point<T> p2) {
		return base_point<T>{ p1.x + p2.x, p1.y + p2.y };
	}

//	template<typename std::enable_if<!std::is_same_v<double, T>, void*>::type = nullptr>
//	operator base_point<double> () {
//		return
//	}
	bool operator== (const base_point& rhs) const
	{
		return x == rhs.x &&
		       y == rhs.y;
	}

	bool operator!= (const base_point& rhs) const
	{
		return !(rhs == *this);
	}
};

using point_d = base_point<double>;
using point_i = base_point<li>;


template<class T>
std::ostream& operator << (std::ostream& os, const base_point<T>& point) {
	os << "{ " << point.x << ", " << point.y << "}";

	return os;
}


/// ________________________________________________________________________________

template<class T>
point_d to_point_d(base_point<T> pnt) {
	return point_d{ double(pnt.x), double(pnt.y) };
}


template<class T>
T dot_product(base_point<T> first, base_point<T> second) {
	return first.x * second.x + first.y * second.y;
}


template<class T>
T cross_product(base_point<T> first, base_point<T> second) {
	return first.x * second.y - first.y * second.x;
}

/// ________________________________________________________________________________

inline base_point<double> line_intersection(double k1, double b1, double k2, double b2) {
	double x = (b2 - b1) / (k1 - k2);
	double y = b1 + k1 * x;

	return base_point<double> { x, y };
}

template<class T>
std::pair<double, double> line_by_points(base_point<T> first, base_point<T> second) {
	double k = (second.y - first.y) / (second.x - first.x);
	double b = first.y - first.x * k;

	return { k, b };
}

inline point_d* line_intersection(point_i l11, point_i l12, point_i l21, point_i l22) {
	if (cross_product(l11 - l12, l21 - l22) == 0) {
		return {};
	}
	// The answer definitely exists:

	if (l11.x == l12.x || l21.x == l22.x) {
		if (l21.x == l22.x) {
			std::swap(l11, l21);
			std::swap(l11, l22);
		}

		return new point_d{
				double(l11.x),
				double(l21.y) + (l11.x - l21.x) * (double((l21.y - l22.y)) / (l21.x - l22.x))
		};
	}
	else {
		// auto[k1, b1] = line_by_points(l11, l12);
		// auto[k2, b2] = line_by_points(l21, l22);

		auto p1 = line_by_points(l11, l12);
		auto p2 = line_by_points(l21, l22);
		auto k1 = p1.first;
		auto b1 = p1.second;
		auto k2 = p2.first;
		auto b2 = p2.second;

		return new point_d{line_intersection(k1, b1, k2, b2)};
	}
}


inline bool point_on_line(point_i pnt, point_i lp1, point_i lp2) {
	return cross_product(lp2 - lp1, pnt - lp1) == 0;
}

inline bool point_in_segment(point_i pnt, point_i sp1, point_i sp2) {
	// Check if the point lies on the right line:
	// &&
	// Check the in this segment:

	return point_on_line(pnt, sp1, sp2) and (dot_product(sp1 - pnt, sp2 - pnt) <= 0);

	//	if (not point_on_line(pnt, sp1, sp2)) { // cross_product(sp2 - sp1, pnt - sp1) != 0) {
//		return false;
//	}

	// std::cout << double(dot_product(sp1 - pnt, sp2 - pnt)) << std::endl;
	// return dot_product(sp1 - pnt, sp2 - pnt) <= 0;
}

inline bool point_on_ray(point_i pnt, point_i rp1, point_i rp2) {
	return point_on_line(pnt, rp1, rp2) and (dot_product(rp2 - rp1, pnt - rp1) >= 0);
}

/// _________________________________________________________________________________________

inline bool point_on_line(point_d pnt, point_d lp1, point_d lp2) {
	return std::abs(cross_product(lp2 - lp1, pnt - lp1)) <= geometry_epsilon;
}

inline bool point_in_segment(point_d pnt, point_d sp1, point_d sp2) {
	return point_on_line(pnt, sp1, sp2) and (dot_product(sp1 - pnt, sp2 - pnt) <= geometry_epsilon);
}

inline bool point_on_ray(point_d pnt, point_d rp1, point_d rp2) {
	return point_on_line(pnt, rp1, rp2) and (dot_product(rp2 - rp1, pnt - rp1) >= -geometry_epsilon);
}

/// _________________________________________________________________________________________


inline bool ray_intersects_segment(point_i rp1, point_i rp2, point_i sp1, point_i sp2) {
	// if they are parallel:
//	if (dot_product(rp1 - rp2, sp1 - sp2) == 0) {
//		return false;
//	}

	auto intersection_point = line_intersection(rp1, rp2, sp1, sp2);
	if (!intersection_point) return false;

//	if (rp1.x == rp2.x) {
//		// Ray is vertical => segment is not!:
//		bool ray_y_increasing = rp2.y > rp1.y;
//
//		double y = ;
//
//		intersection_point = { double(rp1.x), y };
//	}
//	else if (sp1.x == sp2.x) {
//		// Segment is vertical => ray is not!:
//
//	}
//	else {
//		// Two regular (non-vertical) lines:
//		auto[rk, rb] = line_by_points(rp1, rp2);
//		auto[sk, sb] = line_by_points(sp1, sp2);
//
//		intersection_point = line_intersection(rk, rb, sk, sb);
//	}
//	double rk = (rp2.y - rp1.y) / (rp2.x - rp1.x);
//	double s


	// Check for both segment and ray that the point is on it:
	return
			point_in_segment(*intersection_point, to_point_d(sp1), to_point_d(sp2))
			and
			point_on_ray(*intersection_point, to_point_d(rp1), to_point_d(rp2));
}


/// ______________________					Polar sorting:		______________________


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


/// ______________________					Point in polygon:		______________________


inline point_i get_safe_ray_point(point_i point, const std::vector<point_i>& polygon) {
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

/// ______________________					Data reading:		______________________


int main() {

	li n;
	point_i point;
	std::vector<point_i> points;

	std::cin >> n;
	std::cin >> point.x >> point.y;

	for (size_t i = 0; i < n; ++i) {
		points.emplace_back();
		std::cin >> points.back().x >> points.back().y;
	}

	if (point_in_polygon(point, points)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}

	return 0;
}
