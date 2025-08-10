#ifndef _MO_MATH_MATRIX_HPP_
#define _MO_MATH_MATRIX_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/math/matrix.hpp>

namespace mo {

template <internal::traits::Semiring S, int N, int M>
using MatrixN = internal::math::MatrixN<S, N, M>;

}; // namespace mo

#endif
