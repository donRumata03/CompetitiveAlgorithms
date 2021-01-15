//
// Created by Vova on 15.01.2021.
//

#pragma once

#include <olymp_functions.hpp>


/**
 *
 * @param n
 * @return bool maks, ans[i] = true if prime, else: false
 */
std::pair<std::vector<li>, std::vector<li>> eratosphene_sieve_with_lp(li n) {
	std::vector<li> prime(n + 1, true);
	std::vector<li> lp(n + 1, 1);

	prime[0] = prime[1] = false;

	for (size_t i = 2; i * i <= n; ++i) {
		if (prime[i]) {
			// Mark all numbers dividable by i but not by any other prime number before:

			for (size_t j = i * i; j <= n; j += i) {
				prime[j] = false;
				if (lp[j] == 1) {
					lp[j] = i;
				}
			}
			lp[i] = i;
		}
	}

	return { prime, lp };
}

std::vector<li> get_primes_before(li n) {
	auto [sieve, lp] = eratosphene_sieve_with_lp(n);

	std::vector<li> res;
	for (size_t i = 0; i < sieve.size(); ++i) {
		if(sieve[i]) res.push_back(i);
	}

	return res;
}


std::vector<li> factorize_by_lp(li number, const std::vector<li>& lp) {
	std::vector<li> res;

	if (number > lp.size() - 1) {
		throw std::runtime_error("Too big number!");
	}

	li current_number = number;
	while(current_number != 1) {
		auto divisor = lp[current_number];
		std::cout << "lp[" << current_number << "] is " << lp[current_number] << std::endl;
		res.push_back(divisor);
		current_number /= divisor;
	}

	return res;
}

std::vector<std::pair<li, li>> compress_factorization(const std::vector<li>& factorization) {
	std::vector<std::pair<li, li>> res;

	// if (factorization.empty()) return {};
	// res.push_back({ factorization[0], 1 });

	li last_segment_start = 0;
	for (size_t i = 1; i < factorization.size() + 1; ++i) {
		if (i == factorization.size() || factorization[i] != factorization[i - 1]) {
			res.push_back({ factorization[i - 1], i - last_segment_start });
			last_segment_start = i;
		}
	}

	return res;
}




