#ifndef _MO_MATH_QUADRATIC_FIELD_HPP_
#define _MO_MATH_QUADRATIC_FIELD_HPP_

#include <mo/math/field.hpp>
#include <mo/math/utils.hpp>
#include <tuple>

namespace mo {

namespace math {

template <Field F, F::ValueType (*squareFn)()> struct QuadraticField {
    using BaseType = typename F::ValueType;
    using ValueType = std::tuple<BaseType, BaseType>;
    constexpr inline static ValueType zero() {
        return std::make_tuple(F::zero(), F::zero());
    }
    constexpr inline static ValueType one() {
        return std::make_tuple(F::one(), F::zero());
    }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        auto [ax, ay] = a;
        auto [bx, by] = b;
        return std::make_tuple(F::plus(ax, bx), F::plus(ay, by));
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        auto [ax, ay] = a;
        auto [bx, by] = b;
        return std::make_tuple(
            F::plus(F::mul(ax, bx), F::mul(squareFn(), F::mul(ay, by))),
            F::plus(F::mul(ay, bx), F::mul(ax, by)));
    }
    constexpr inline static ValueType neg(ValueType a) {
        auto [ax, ay] = a;
        return std::make_tuple(F::neg(ax), F::neg(ay));
    }
    constexpr inline static ValueType inv(ValueType a) {
        auto [ax, ay] = a;
        assert(ax != F::zero() || ay != F::zero());
        auto denom =
            F::plus(F::mul(ax, ax), F::neg(F::mul(squareFn(), F::mul(ay, ay))));
        assert(denom != 0);
        auto denomInv = F::inv(denom);
        return std::make_tuple(F::mul(ax, denomInv),
                               F::mul(F::neg(ay), denomInv));
    }
};

}; // namespace math

}; // namespace mo

#endif
