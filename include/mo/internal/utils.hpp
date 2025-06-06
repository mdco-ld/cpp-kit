#ifndef _MO_INTERNAL_UTILS_HPP_
#define _MO_INTERNAL_UTILS_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/concepts/semigroup.hpp>

#include <algorithm>
#include <limits>
#include <type_traits>
#include <utility>
#include <bit>

namespace mo::internal::utils {

namespace impl {

template <typename Int>
concept Integral = std::is_integral_v<Int> || std::is_same_v<Int, __int128>;

using ull = unsigned long long;

template <typename Int>
    requires Integral<Int>
constexpr Int gcd(Int a, Int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

template <typename Int>
    requires Integral<Int>
constexpr Int lcm(Int a, Int b) {
    a /= gcd(a, b);
    return a * b;
}

template <typename Int>
    requires std::is_integral_v<Int>
constexpr inline int popcount(Int x) {
    return std::popcount(static_cast<ull>(x));
}

template <typename Int>
    requires std::is_integral_v<Int>
constexpr inline int bitWidth(Int x) {
    return std::bit_width(static_cast<ull>(x));
}

/**
 * returns floor(log2(x))
 */
template <typename Int>
    requires std::is_integral_v<Int>
constexpr inline int log2(Int x) {
    return bitWidth(x) - 1;
}

}; // namespace impl

namespace traits {

template <class Int> struct MaxMonoid {
    Int value;
    MaxMonoid() : value(std::numeric_limits<Int>::min()) {}
    MaxMonoid(Int val) : value(val) {}
    MaxMonoid operator+(const MaxMonoid other) const {
        return std::max(value, other.value);
    }
    MaxMonoid &operator+=(const MaxMonoid other) {
        value = std::max(value, other, value);
        return *this;
    }
};

template <class Int> struct MinMonoid {
    Int value;
    MinMonoid() : value(std::numeric_limits<Int>::max()) {}
    MinMonoid(Int val) : value(val) {}
    MinMonoid operator+(const MinMonoid other) const {
        return std::min(value, other.value);
    }
    MinMonoid &operator+=(const MinMonoid other) {
        value = std::min(value, other.value);
        return *this;
    }
};

template <class Int> struct GcdMonoid {
    Int value;
    GcdMonoid() : value(Int{0}) {}
    GcdMonoid(Int val) : value(val) {}
    GcdMonoid operator+(const GcdMonoid other) const {
        return impl::gcd(value, other.value);
    }
    GcdMonoid &operator+=(const GcdMonoid other) {
        value = impl::gcd(value, other.value);
        return *this;
    }
};

template <class Int> struct LcmMonoid {
    Int value;
    LcmMonoid() : value(Int{0}) {}
    LcmMonoid(Int val) : value(val) {}
    LcmMonoid operator+(const LcmMonoid other) const {
        return impl::lcm(value, other.value);
    }
    LcmMonoid &operator+=(const LcmMonoid other) {
        value = impl::lcm(value, other.value);
        return *this;
    }
};

static_assert(internal::traits::Monoid<MaxMonoid<int>>);
static_assert(internal::traits::Monoid<MinMonoid<int>>);
static_assert(internal::traits::Monoid<GcdMonoid<int>>);
static_assert(internal::traits::Monoid<LcmMonoid<int>>);

}; // namespace traits

}; // namespace mo::internal::utils

#endif
