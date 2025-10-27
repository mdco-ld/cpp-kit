#ifndef _MOG_INTERNAL_MATH_COMPUTATIONS_HPP_
#define _MOG_INTERNAL_MATH_COMPUTATIONS_HPP_

#include <mog/internal/concepts/semiring.hpp>
#include <mog/internal/math/matrix.hpp>
#include <mog/internal/numeric.hpp>

namespace mog::internal::math {

template <numeric::Integral Int>
constexpr Int floorSum(Int n, Int a, Int b, Int m) {
	Int ans = 0;
	if (a >= m) {
		ans += (a / m) * n * (n - 1) / 2;
		a %= m;
	}
	if (b >= m) {
		ans += n * (b / m);
		b %= m;
	}
	if (a == 0) {
		return ans;
	}
	if (n == 0) {
		return ans;
	}
	Int y = (a * n + b) / m;
	if (y == 0) {
		return ans;
	}
	ans += floorSum(y, m, (a * n + b) % m, a);
	return ans;
}

template <traits::Semiring S> constexpr S geometricSum(S x, int n) {
	using Mat = MatrixN<S, 2, 2>;
	Mat mat;
	mat[0][0] = x;
	mat[0][1] = S{0};
	mat[1][0] = S{1};
	mat[1][1] = S{1};
	Mat mat2 = mat.pow(n + 1);
	return mat2[1][0];
}

template <traits::Semiring S>
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

}; // namespace mog::internal::math

#endif
