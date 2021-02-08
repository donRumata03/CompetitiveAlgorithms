//
// Created by Vova on 31.01.2021.
//

#pragma once

#include <olymp_functions.hpp>


constexpr double geometry_epsilon = 1e-10;


template<class T = li>
struct base_point {
	T x {};
	T y {};

	friend base_point<T> operator- (base_point<T> p1, base_point<T> p2) {
		return { p1.x - p2.x, p1.y - p2.y };
	}

	friend base_point<T> operator+ (base_point<T> p1, base_point<T> p2) {
		return { p1.x + p2.x, p1.y + p2.y };
	}

//	template<typename std::enable_if<!std::is_same_v<double, T>, void*>::type = nullptr>
//	operator base_point<double> () {
//		return
//	}
};

using point_d = base_point<double>;
using point_i = base_point<li>;


template<class T>
point_d to_point_d(base_point<T> pnt) {
	return { double(pnt.x), double(pnt.y) };
}


template<class T>
T dot_product(base_point<T> first, base_point<T> second) {
	return first.x * second.x + first.y * second.y;
}


template<class T>
T cross_product(base_point<T> first, base_point<T> second) {
	return first.x * second.y - first.y * second.x;
}

// ________________________________________________________________________________

inline base_point<double> line_intersection(double k1, double b1, double k2, double b2) {
	double x = (b2 - b1) / (k1 - k2);
	double y = b1 + k1 * x;

	return { x, y };
}

template<class T>
std::pair<double, double> line_by_points(base_point<T> first, base_point<T> second) {
	double k = (second.y - first.y) / (second.x - first.x);
	double b = first.y - first.x * k;

	return { k, b };
}

inline std::optional<point_d> line_intersection(point_i l11, point_i l12, point_i l21, point_i l22) {
	if (cross_product(l11 - l12, l21 - l22) == 0) {
		return {};
	}
	// The answer definitely exists:

	if (l11.x == l12.x || l21.x == l22.x) {
		if (l21.x == l22.x) {
			std::swap(l11, l21);
			std::swap(l11, l22);
		}

		return point_d{
			double(l11.x),
			double(l21.y) + (l11.x - l21.x) * (double((l21.y - l22.y)) / (l21.x - l22.x))
		};
	}
	else {
		auto[k1, b1] = line_by_points(l11, l12);
		auto[k2, b2] = line_by_points(l21, l22);

		return line_intersection(k1, b1, k2, b2);
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



