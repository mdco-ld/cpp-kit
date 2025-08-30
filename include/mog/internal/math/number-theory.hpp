#ifndef _MOG_INTERNAL_NUMBER_THEORY_HPP_
#define _MOG_INTERNAL_NUMBER_THEORY_HPP_

#include <vector>

namespace mog::internal {

namespace number_theory {

using u128 = __uint128_t;
using u64 = unsigned long long;
using i64= long long;

static constexpr std::vector<unsigned int> getSmallPrimes() {
	return {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
}

static u64 binPow(u64 x, u64 n, u64 mod) {
	u64 result = 1;
	while (n) {
		if (n & 1) {
			result = ((u128)result * x) % mod;
		}
		x = ((u128)x * x) % mod;
		n >>= 1;
	}
	return result;
}

static bool millerRabin(u64 n, u64 b) {
	u64 m = n - 1;
	int k = 0;
	while (!(m & 1)) {
		k++;
		m >>= 1;
	}
	b = binPow(b, m, n);
	if (b == 1 || b == n - 1) {
		return true;
	}
	for (auto p : getSmallPrimes()) {
		u64 d = b;
		for (int i = 1; i < k; i++) {
			d = u128(d) * d % n;
			if (d == n - 1) {
				return true;
			}
		}
	}
	return false;
}

static bool isPrime(u64 n) {
	if (n < 2) {
		return false;
	}
	for (unsigned int p : getSmallPrimes()) {
		if (n == p) {
			return true;
		}
		if (n % p == 0) {
			return false;
		}
	}
	for (auto p : getSmallPrimes()) {
		if (!millerRabin(n, p)) {
			return false;
		}
	}
	return true;
}

}; // namespace number_theory

}; // namespace mog::internal

#endif
