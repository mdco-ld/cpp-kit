#ifndef _MO_INTERNAL_UTILS_HPP_
#define _MO_INTERNAL_UTILS_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/concepts/semigroup.hpp>
#include <mo/internal/numeric.hpp>

#include <algorithm>
#include <limits>

namespace mo::internal::utils {

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
        return numeric::gcd(value, other.value);
    }
    GcdMonoid &operator+=(const GcdMonoid other) {
        value = numeric::gcd(value, other.value);
        return *this;
    }
};

template <class Int> struct LcmMonoid {
    Int value;
    LcmMonoid() : value(Int{0}) {}
    LcmMonoid(Int val) : value(val) {}
    LcmMonoid operator+(const LcmMonoid other) const {
        return numeric::lcm(value, other.value);
    }
    LcmMonoid &operator+=(const LcmMonoid other) {
        value = numeric::lcm(value, other.value);
        return *this;
    }
};

template<class T> struct ProductMonoid {
	T value;
	ProductMonoid() requires numeric::Integral<T> : value(T{1}) {}
	ProductMonoid() requires (!numeric::Integral<T>) : value(T{}) {}
	ProductMonoid(T val) : value(val) {}
	ProductMonoid operator+(const ProductMonoid other) const {
		return value * other.value;
	}
	ProductMonoid &operator+=(const ProductMonoid other) {
		value *= other.value;
		return *this;
	}
};

static_assert(internal::traits::Monoid<MaxMonoid<int>>);
static_assert(internal::traits::Monoid<MinMonoid<int>>);
static_assert(internal::traits::Monoid<GcdMonoid<int>>);
static_assert(internal::traits::Monoid<LcmMonoid<int>>);
static_assert(internal::traits::Monoid<ProductMonoid<int>>);

}; // namespace traits

}; // namespace mo::internal::utils

#endif
