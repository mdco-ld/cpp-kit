#ifndef _MOG_INTERNAL_SIEVE_HPP_
#define _MOG_INTERNAL_SIEVE_HPP_

#include <vector>

namespace mog::internal::sieve {

class LinearSieve {
  public:
	LinearSieve(int N) : spf(N) {
		for (int i = 2; i < N; i++) {
			if (spf[i] == 0) {
				primes.push_back(i);
				spf[i] = i;
			}
			for (int j = 0; primes[j] * i < N; j++) {
				spf[primes[j] * i] = primes[j];
				if (primes[j] == spf[i]) {
					break;
				}
			}
		}
	}

	inline bool isPrime(int x) { return spf[x] == x; }

	inline int getPrime(int i) { return primes[i]; }

	inline const std::vector<int> &getPrimes() { return primes; }

	inline int getSpf(int x) { return spf[x]; }

  private:
	std::vector<int> primes;
	std::vector<int> spf;
};

}; // namespace mog::internal::sieve

#endif
