#ifndef _MOG_MATH_COMPUTATIONS_HPP_
#define _MOG_MATH_COMPUTATIONS_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/math/computations.hpp>
#include <mog/internal/numeric.hpp>

namespace mog {

template <internal::traits::Semiring S>
constexpr auto geometricSum = internal::math::geometricSum<S>;

template <internal::traits::Semiring S>
constexpr auto binPow = internal::math::binaryPower<S>;

template<internal::numeric::Integral Int>
constexpr auto isqrt = internal::numeric::isqrt<Int>;

}; // namespace mog

#endif
