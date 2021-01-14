//
// Created by Vova on 14.01.2021.
//

#pragma once


#include <data_structures/DSU.h>

inline void output_dsu(const DSU& dsu) {
	std::cout << "Size: " << dsu.size() << std::endl;
	std::cout << "Tree structure: " << std::endl;
	for (size_t i = 0; i < dsu.size(); ++i) {
		std::cout << dsu.find(i) << " ";
	}

	std::cout << std::endl << "Sizes: " << std::endl;
	for (size_t i = 0; i < dsu.size(); ++i) {
		std::cout << dsu.sizes[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

inline void test_dsu_working_ability() {
	DSU dsu(10);

	std::cout << "Before: " << std::endl;
	output_dsu(dsu);

	// Make these sets:
	// 1. { 0, 1, 2, 3, 4 }
	// 2. { 5, 9 }
	// 3. { 6, 7, 8 }

	dsu.unite(1, 2);
	dsu.unite(1, 4);
	dsu.unite(2, 0);
	dsu.unite(1, 3);

	dsu.unite(5, 9);

	dsu.unite(6, 7);
	dsu.unite(7, 8);


	std::cout << "After: " << std::endl;
	output_dsu(dsu);

	std::cout << "Dumped set: " << std::endl;
	for(auto s : dsu.dump_sets()) {
		std::cout << s << std::endl;
	}
}



inline void test_dsu_computational_complexity() {

}

