#ifndef _MO_MATH_GROUP_HPP_
#define _MO_MATH_GROUP_HPP_

#include <mo/math/monoid.hpp>

#include <concepts>

namespace mo {

namespace math {

template <typename T>
concept Group = Monoid<T> && requires(T::ValueType a) {
    { T::neg(a) } -> std::same_as<typename T::ValueType>;
};

template <typename T, T (*negFn)(T), T (*plusFn)(T, T), T (*zeroFn)()>
struct GroupOf {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return plusFn(a, b);
    }
    constexpr inline static ValueType neg(ValueType a) { return negFn(a); }
};

template <typename T, T (*oneFn)()> struct DefaultGroup {
    using ValueType = T;
    constexpr inline static ValueType zero() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
};

template <typename T, T zeroValue = T{0}> struct BasicGroup {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroValue; }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
};

}; // namespace math

}; // namespace mo

#endif
