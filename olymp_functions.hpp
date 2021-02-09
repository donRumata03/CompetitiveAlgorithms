//
// Created by Vova on 22.11.2020.
//

#pragma once

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



/// 												Floating Point Utilities:

template <class Float, std::enable_if_t<std::is_floating_point_v<Float>, void*> nothing = nullptr>
bool almost_equal(Float float1, Float float2, Float relative_eps = 1e-10, Float absolute_eps = 1e-15) {
	if (float1 == float2) return true;
	if ((float1 + float2) == 0) return false;
	if(float1 == 0) return std::abs(float2) < absolute_eps;
	if(float2 == 0) return std::abs(float1) < absolute_eps;
	return std::abs((float1 - float2) / (float1 + float2)) < relative_eps;
}
