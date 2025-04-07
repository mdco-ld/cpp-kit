#ifndef _MO_MATH_MONOID_HPP_
#define _MO_MATH_MONOID_HPP_

#include <concepts>

namespace mo {

namespace math {

template <typename T>
concept Monoid = requires(T::ValueType a, T::ValueType b) {
    { T::zero() } -> std::same_as<typename T::ValueType>;
    { T::plus(a, b) } -> std::same_as<typename T::ValueType>;
};

template <typename T, T (*plusFn)(T, T), T (*zeroFn)()> struct MonoidOf {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return plusFn(a, b);
    }
};

template <typename T, T (*oneFn)()> struct DefaultMonoid {
    using ValueType = T;
    constexpr inline static ValueType zero() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
};

template <typename T, T zeroValue = T{0}> struct BasicMonoid {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroValue; }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
};

}; // namespace math

}; // namespace mo

#endif
