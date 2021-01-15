//
// Created by Vova on 15.01.2021.
//

#pragma once


#include <numeric/eratosphene_sieve.h>


inline void test_eratosphene_factorization() {
	auto [sieve, lp] = eratosphene_sieve_with_lp(10'000'00);
	// std::cout << "Primes: " << get_primes_before(100) << std::endl;

	// std::cout << sieve << std::endl;
	// std::cout << lp << std::endl;


	auto test_number = 2 * 2 * 3 * 3 * 7 * 131;
	std::cout << "Testing number " << test_number << std::endl;
	std::cout << "Answer is: " << factorize_by_lp(test_number, lp) << std::endl;

	std::cout << "Compressed factorization: " << std::endl;
	for (auto p : compress_factorization(factorize_by_lp(test_number, lp))) {
		std::cout << p.first << "^" << p.second << std::endl;
	}
}
