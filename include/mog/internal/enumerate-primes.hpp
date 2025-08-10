#ifndef _MOG_INTERNAL_ENUMERATE_PRIMES_HPP_
#define _MOG_INTERNAL_ENUMERATE_PRIMES_HPP_

#include <vector>

namespace mog::internal::sieve {

constexpr std::vector<int> enumeratePrimes(int N) {
	std::vector<int> spf(N);
	std::vector<int> primes;

	for (int i = 2; i < N; i++) {
		if (spf[i] == 0) {
			spf[i] = i;
			primes.push_back(i);
		}
		for (int j = 0; primes[j] * i < N; j++) {
			spf[primes[j] * i] = primes[j];
			if (primes[j] == spf[i]) {
				break;
			}
		}
	}
	return primes;
}

}; // namespace mog::internal::sieve

#endif
