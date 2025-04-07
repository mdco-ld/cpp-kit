#ifndef _MO_MATH_SEMIRING_HPP_
#define _MO_MATH_SEMIRING_HPP_

#include <concepts>

namespace mo {

namespace math {

template <typename T>
concept Semiring = requires(T::ValueType a, T::ValueType b) {
    { T::zero() } -> std::same_as<typename T::ValueType>;
    { T::one() } -> std::same_as<typename T::ValueType>;
    { T::plus(a, b) } -> std::same_as<typename T::ValueType>;
    { T::mul(a, b) } -> std::same_as<typename T::ValueType>;
};

template <typename T, T (*plusFn)(T, T), T (*mulFn)(T, T), T (*zeroFn)(),
          T (*oneFn)()>
struct SemiringOf {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return plusFn(a, b);
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return mulFn(a, b);
    }
};

template <typename T, T (*zeroFn)(), T (*oneFn)()> struct DefaultSemiring {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
};

template <typename T, T zeroValue = T{0}, T oneValue = T{1}>
struct BasicSemiring {
    using ValueType = T;
    constexpr inline static ValueType zero() { return zeroValue; }
    constexpr inline static ValueType one() { return oneValue; }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
};

}; // namespace math

}; // namespace mo

#endif
