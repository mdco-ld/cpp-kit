#ifndef _MO_MATH_UTILS_HPP_
#define _MO_MATH_UTILS_HPP_

#include <mo/math/field.hpp>
#include <mo/math/matrix.hpp>
#include <mo/math/modint.hpp>
#include <mo/math/ring.hpp>
#include <mo/utils.hpp>

#include <cstdint>

namespace mo {

namespace math {

template <Semiring S> S::ValueType binPowS(typename S::ValueType x, int64_t e) {
    typename S::ValueType result = S::one();
    while (e > 0) {
        if (e & 1) {
            result = S::mul(result, x);
        }
        e >>= 1;
        x = S::mul(x, x);
    }
    return result;
}

template <Field F> F::ValueType binPow(typename F::ValueType x, int64_t e) {
    if (e < 0) {
        x = F::inv(x);
        e = -e;
    }
    typename F::ValueType result = F::one();
    while (e > 0) {
        if (e & 1) {
            result = F::mul(result, x);
        }
        e >>= 1;
        x = F::mul(x, x);
    }
    return result;
}

using Int32Ring = BasicRing<int32_t>;
using Int64Ring = BasicRing<int64_t>;
using FloatField = BasicField<float>;
using DoubleField = BasicField<double>;
using LDoubleField = BasicField<long double>;
using F1000000007 = DefaultField<ModInt1000000007, constfn(ModInt1000000007(0)),
                                 constfn(ModInt1000000007(1))>;
using F998244353 = DefaultField<ModInt998244353, constfn(ModInt998244353(0)),
                                constfn(ModInt998244353(1))>;
template <int64_t MOD>
using Fn =
    DefaultField<ModInt<MOD>, constfn(ModInt<MOD>(0)), constfn(ModInt<MOD>(0))>;
template <int64_t MOD>
using Zn =
    DefaultRing<ModInt<MOD>, constfn(ModInt<MOD>(0)), constfn(ModInt<MOD>(0))>;

}; // namespace math

}; // namespace mo

#endif
