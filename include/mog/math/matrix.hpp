#ifndef _MOG_MATH_MATRIX_HPP_
#define _MOG_MATH_MATRIX_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/math/matrix.hpp>

namespace mog {

template <internal::traits::Semiring S, int N, int M>
using MatrixN = internal::math::MatrixN<S, N, M>;

}; // namespace mog

#endif
