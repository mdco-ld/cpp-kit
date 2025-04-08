#ifndef _MO_MATH_UTILS_HPP_
#define _MO_MATH_UTILS_HPP_

#include <mo/math/field.hpp>
#include <mo/math/ring.hpp>

#include <cstdint>

namespace mo {

namespace math {

using Int32Ring = BasicRing<int32_t>;
using Int64Ring = BasicRing<int64_t>;
using FloatField = BasicField<float>;
using DoubleField = BasicField<double>;
using LDoubleField= BasicField<long double>;

};

};

#endif
