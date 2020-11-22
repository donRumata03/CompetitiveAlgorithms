//
// Created by Vova on 22.11.2020.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vector) {
	for (auto& v: vector) os << v << " ";
	os << std::endl;

	return os;
}
