//
// Created by Vova on 14.01.2021.
//

#pragma once

#include <olymp_funcions.hpp>


class DSU {
	std::vector<li> sizes;
	std::vector<li> data;
	li n = 0;

public:
	DSU() = default;
	DSU(li _n) : data(_n), sizes(_n, 1) {
		std::iota(data.begin(), data.end(), 0);
	}

	/**
	 * @returns the index of element representing the set of the element
	 */
	li find(li element) {
		if (data[element] == element) return element;

		return data[element] = find(element);
	}

	/**
	 * unites sets in which the elements are situated
	 * @returns the resultant set representation element index
	 */
	li unite(li first, li second) {
		first = find(first);
		second = find(second);

		if (first == second) return first;

		// add second to first, first should be bigger of equal:
		if (sizes[first] < sizes[second]) std::swap(first, second);

		data[second] = first;
		sizes[first] += sizes[second];

		return first;
	}

	/**
	 * Makes a new set with root of the vertex at «index»
	 * BREAKS SIZE HEURISTIC!
	 */
	void make_set(li index) {
		data[index] = index;
		sizes[index] = 1;
	}
};
