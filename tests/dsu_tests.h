//
// Created by Vova on 14.01.2021.
//

#pragma once


#include <data_structures/DSU.h>
#include <chrono>
#include <random>

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


double measure_DSU_time(li n) {
	li repetitions = 10;
	li operations = li(std::round(n * 2.));

	// Generate queries:
	std::vector<std::pair<li, li>> queries(operations);
	auto gen = std::mt19937_64 { std::random_device{}() };
	auto rand_element = [&gen, &n]() -> li { return gen() % n; };
	std::generate(queries.begin(), queries.end(), [&rand_element](){
		return std::pair{ rand_element(), rand_element() };
	});

	auto starting_time = std::chrono::high_resolution_clock::now();

	for (size_t repetition = 0; repetition < repetitions; ++repetition) {
		DSU dsu(n);
		for (size_t i = 0; i < operations; ++i) {
			dsu.unite(queries[i].first, queries[i].second);
		}
		std::cout << dsu.dump_sets().size() << " sets total (of " << n << ")" << std::endl;
	}
	std::chrono::nanoseconds time_elapsed = std::chrono::high_resolution_clock::now() - starting_time;
	double ns_per_one_iteration = time_elapsed.count() / (repetitions * operations);

	return ns_per_one_iteration;
}

inline void test_dsu_computational_complexity() {
	li N = 10'000'000;

//	std::cout << measure_DSU_time(N / 10) << std::endl;
//	std::cout << measure_DSU_time(N / 5) << std::endl;
//	std::cout << measure_DSU_time(N / 2) << std::endl;
//	std::cout << measure_DSU_time(N) << std::endl;


	std::vector<double> Ns = {
			N / 10., N / 9., N / 8., N / 7., N / 5., N / 4., N / 3., N / 2., N / 1.
	};
	std::vector<double> times = {

	};

	for(auto& n : Ns) {
		times.push_back(measure_DSU_time(li(n)));

	}

	std::cout << std::fixed << Ns << std::endl;
	std::cout << times << std::endl;
}

