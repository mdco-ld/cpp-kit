#ifndef _MO_INTERNAL_MATH_COMPUTATIONS_HPP_
#define _MO_INTERNAL_MATH_COMPUTATIONS_HPP_

#include <mo/internal/math/matrix.hpp>
#include <mo/internal/concepts/semiring.hpp>

namespace mo::internal::math {

template <traits::Semiring S>
constexpr S geometricSum(S x, int n) {
	using Mat = MatrixN<S, 2, 2>;
	Mat mat;
	mat[0][0] = x;
	mat[0][1] = S{0};
	mat[1][0] = S{1};
	mat[1][1] = S{1};
	Mat mat2 = mat.pow(n + 1);
	return mat2[1][0];
}

template<traits::Semiring S>
constexpr S binaryPower(S x, unsigned long long n) {
	S result = S{1};
	S base = x;
	while (n) {
		if (n & 1) {
			result *= base;
		}
		n >>= 1;
		base *= base;
	}
	return result;
}

};

#endif
