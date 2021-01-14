//
// Created by Vova on 22.11.2020.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <utility>
#include <fstream>

#include <unordered_set>
#include <unordered_map>


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
