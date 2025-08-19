#ifndef _MOG_MATH_MATRIX_HPP_
#define _MOG_MATH_MATRIX_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/math/matrix.hpp>

namespace mog {

template <internal::traits::Semiring S, int N, int M>
using MatrixN = internal::math::MatrixN<S, N, M>;

template<int N, int M, internal::traits::Semiring S>
MatrixN<S, N, M> matrixOf(std::initializer_list<std::initializer_list<S>> mat) {
	MatrixN<S, N, M> ret;
	int i = 0;
	for (auto row: mat) {
		int j = 0;
		for (auto elem: row) {
			ret[i][j] = elem;
			j++;
		}
		i++;
	}
	return ret;
}

}; // namespace mog

#endif
