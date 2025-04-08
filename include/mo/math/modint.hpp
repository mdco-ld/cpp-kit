#ifndef _MO_MATH_MODINT_HPP_
#define _MO_MATH_MODINT_HPP_

#include <concepts>
#include <cstdint>
#include <tuple>

namespace mo {

namespace math {

template <std::integral T> constexpr T extendedEuclid(T a, T b, T &x, T &y) {
    x = 1;
    y = 0;
    T x1 = 0;
    T y1 = 1;
    while (b) {
        T q = a / b;
        std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
        std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
        std::tie(a, b) = std::make_tuple(b, a - q * b);
    }
    return a;
}

template <int64_t MOD> class ModInt {
  public:
    constexpr ModInt() : value(0) {}
    constexpr ModInt(int64_t x) : value(x) {
        value %= MOD;
        if (value < 0) {
            value += MOD;
        }
    }

    constexpr inline ModInt operator+(ModInt other) {
        return value + other.value;
    }
    constexpr inline ModInt operator-(ModInt other) {
        return value - other.value;
    }
    constexpr inline ModInt operator*(ModInt other) {
        return value * other.value;
    }
    constexpr inline ModInt operator/(ModInt other) {
        return (*this) * other.inverse();
    }
    constexpr inline ModInt operator-() { return -value; }
    constexpr inline int64_t toInt() { return value; }
    constexpr ModInt inverse() {
        int64_t x, y;
        extendedEuclid(value, MOD, x, y);
        return x;
    }

    ModInt inline &operator+=(ModInt other) {
        value += other.value;
        value %= MOD;
        return *this;
    }
    ModInt inline &operator*=(ModInt other) {
        value *= other.value;
        value %= MOD;
        return *this;
    }
    ModInt inline &operator-=(ModInt other) {
        value -= other.value;
        value %= MOD;
        if (value < 0) {
            value += MOD;
        }
        return *this;
    }
    ModInt inline &operator/=(ModInt other) {
        return *this = (*this) * other.inverse();
    }

  private:
    int64_t value;
};

using ModInt998244353 = ModInt<998244353>;
using ModInt1000000007 = ModInt<1000000007>;

namespace tests {

}; // namespace tests

}; // namespace math

}; // namespace mo

#endif
