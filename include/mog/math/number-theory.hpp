#ifndef _MOG_NUMBER_THEORY_HPP_
#define _MOG_NUMBER_THEORY_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/math/number-theory.hpp>

namespace mog {

static inline bool isPrime(long long n) {
	if (n < 4) {
		return n == 2 || n == 3;
	}
	return internal::number_theory::isPrime(n);
}

static inline bool isPrime(unsigned long long n) {
	if (n < 4) {
		return n == 2 || n == 3;
	}
	return internal::number_theory::isPrime(n);
}

};

#endif
