//
// Created by Vova on 14.01.2021.
//

#pragma once

#include <olymp_functions.hpp>



class DSU {
	std::vector<li> sizes;
	mutable std::vector<li> data;
	li n = 0;

public:
	DSU() = default;
	DSU(li _n) : n(_n), data(_n), sizes(_n, 1) {
		std::iota(data.begin(), data.end(), 0);
	}

	[[nodiscard]] li size() const { return n; }

	/**
	 * @returns the index of element representing the set of the element
	 */
	li find(li element) const {
		if (data[element] == element) return element;

		return data[element] = find(data[element]);
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


	std::vector<std::vector<li>> dump_sets() const {
		std::vector<std::vector<li>> res;

		auto set_indexes_set = std::unordered_set<li>(data.begin(), data.end());
		li set_number = set_indexes_set.size();
		// std::cout << "Different sets found: " << set_number << std::endl;

		res.resize(set_number);

		// Enumerate sets:
		std::unordered_map<li, li> set_repersentor_to_index_converter;
		set_repersentor_to_index_converter.reserve(set_number);

		li this_set_index = 0;
		for (auto& it : set_indexes_set) {
			set_repersentor_to_index_converter[it] = this_set_index;
			this_set_index++;
		}

		// for(auto& it : set_repersentor_to_index_converter) std::cout << it << std::endl;

		for (li i = 0; i < n; ++i) {
			auto set_representor = find(i);
			auto new_set_index = set_repersentor_to_index_converter[set_representor];
			res[new_set_index].push_back(i);
		}

		return res;
	}


	// ________________________________
	friend void output_dsu(const DSU&);
};
