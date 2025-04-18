#ifndef _MO_MATH_FIELD_HPP_
#define _MO_MATH_FIELD_HPP_

#include <mo/math/ring.hpp>

#include <concepts>

namespace mo {

namespace math {

template <typename T>
concept Field = Ring<T> && requires(T::ValueType x, T::ValueType y, T::BaseType base) {
    { T::inv(x) } -> std::same_as<typename T::ValueType>;
	{ T::make(base) } -> std::same_as<typename T::ValueType>;
};

template <typename T, T (*plusFn)(T, T), T (*mulFn)(T, T), T (*negFn)(T),
          T (*invFn)(T), T (*zeroFn)(), T (*oneFn)()>
class FieldOf {
    using ValueType = T;
    using BaseType = T;
    constexpr inline static ValueType make(BaseType value) {
        return ValueType{value};
    }
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return plusFn(a, b);
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return mulFn(a, b);
    }
    constexpr inline static ValueType neg(ValueType a) { return negFn(a); }
    constexpr inline static ValueType inv(ValueType a) { return invFn(a); }
};

template <typename T, T (*zeroFn)(), T (*oneFn)()> struct DefaultField {
    using ValueType = T;
    using BaseType = T;
    constexpr inline static ValueType make(BaseType value) {
        return ValueType{value};
    }
    constexpr inline static ValueType zero() { return zeroFn(); }
    constexpr inline static ValueType one() { return oneFn(); }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
    constexpr inline static ValueType inv(ValueType a) { return oneFn() / a; }
};

template <typename T, T zeroValue = T{0}, T oneValue = T{1}> struct BasicField {
    using ValueType = T;
    using BaseType = T;
    constexpr inline static ValueType make(BaseType value) {
        return ValueType{value};
    }
    constexpr inline static ValueType zero() { return zeroValue; }
    constexpr inline static ValueType one() { return oneValue; }
    constexpr inline static ValueType plus(ValueType a, ValueType b) {
        return a + b;
    }
    constexpr inline static ValueType mul(ValueType a, ValueType b) {
        return a * b;
    }
    constexpr inline static ValueType neg(ValueType a) { return -a; }
    constexpr inline static ValueType inv(ValueType a) { return oneValue / a; }
};

}; // namespace math

}; // namespace mo

#endif
