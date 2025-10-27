#ifndef _MOG_MATH_COMPUTATIONS_HPP_
#define _MOG_MATH_COMPUTATIONS_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/math/computations.hpp>
#include <mog/internal/numeric.hpp>

namespace mog {

template <internal::numeric::Integral Int>
inline Int floorSum(Int n, Int a, Int b, Int m) {
	return internal::math::floorSum(n, a, b, m);
}

template <internal::traits::Semiring S> inline S geometricSum(S x, int n) {
	return internal::math::geometricSum(x, n);
}

template <internal::traits::Semiring S>
inline S binPow(S x, unsigned long long n) {
	return internal::math::binaryPower<S>;
}

template <internal::numeric::Integral Int> inline Int isqrt(Int x) {
	return internal::numeric::isqrt(x);
}

}; // namespace mog

#endif
