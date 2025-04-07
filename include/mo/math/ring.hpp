#ifndef _MO_MATH_RING_HPP_
#define _MO_MATH_RING_HPP_

#include <mo/math/semiring.hpp>

#include <concepts>

namespace mo {

namespace math {

template <typename T>
concept Ring = Semiring<T> && requires(T::ValueType x) {
    { T::neg(x) } -> std::same_as<typename T::ValueType>;
};

template <typename T, T (*plusFn)(T, T), T (*mulFn)(T, T), T (*negFn)(T),
          T (*zeroFn)(), T (*oneFn)()>
class RingOf {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return plusFn(a, b);
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return mulFn(a, b);
    }
    constexpr inline static ValueType neg(ValueType a) { return negFn(a); }
};

template <typename T, T (*zeroFn)(), T (*oneFn)()> struct DefaultRing {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
};

template <typename T, T zeroValue = T{0}, T oneValue = T{1}> struct BasicRing {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroValue; }
    constexpr inline static ValueType one() { return oneValue; }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
};

}; // namespace math

}; // namespace mo

#endif
