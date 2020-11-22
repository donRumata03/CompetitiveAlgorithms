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


template<class FirstT, class SecondT>
std::ostream& operator << (std::ostream& os, const std::pair<FirstT, SecondT>& pair) {
	os << "(" << pair.first << ", " << pair.second << ")";

	return os;
}


template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vector) {
	for (auto& v: vector) os << v << " ";

	return os;
}
