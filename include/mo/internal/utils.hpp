#ifndef _MO_INTERNAL_UTILS_HPP_
#define _MO_INTERNAL_UTILS_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/concepts/semigroup.hpp>
#include <mo/internal/numeric.hpp>

#include <algorithm>
#include <limits>
#include <tuple>
#include <utility>

namespace mo::internal::utils {

template <typename T> struct limits;

template <class T>
	requires numeric::Integral<T>
struct limits<T> {
	static constexpr T maxValue() { return std::numeric_limits<T>::max(); }
	static constexpr T minValue() { return std::numeric_limits<T>::min(); }
};

template <class A, class B> struct limits<std::pair<A, B>> {
	static constexpr std::pair<A, B> maxValue() {
		return std::make_pair(limits<A>::maxValue(), limits<B>::maxValue());
	}
	static constexpr std::pair<A, B> minValue() {
		return std::make_pair(limits<A>::minValue(), limits<B>::minValue());
	}
};

template <class... Ts> struct limits<std::tuple<Ts...>> {
	static constexpr std::tuple<Ts...> maxValue() {
		return {(limits<Ts>::maxValue())...};
	}
	static constexpr std::tuple<Ts...> minValue() {
		return {(limits<Ts>::minValue())...};
	}
};

namespace traits {

template <class T> struct MaxMonoid {
	T value;
	MaxMonoid() : value(limits<T>::minValue()) {}
	MaxMonoid(T val) : value(val) {}
	MaxMonoid operator+(const MaxMonoid other) const {
		return std::max(value, other.value);
	}
	MaxMonoid &operator+=(const MaxMonoid other) {
		value = std::max(value, other, value);
		return *this;
	}
};

template <class T> struct MinMonoid {
	T value;
	MinMonoid() : value(limits<T>::maxValue()) {}
	MinMonoid(T val) : value(val) {}
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

template <class T> struct ProductMonoid {
	T value;
	ProductMonoid()
		requires numeric::Integral<T>
		: value(T{1}) {}
	ProductMonoid()
		requires(!numeric::Integral<T>)
		: value(T{}) {}
	ProductMonoid(T val) : value(val) {}
	ProductMonoid operator+(const ProductMonoid other) const {
		return value * other.value;
	}
	ProductMonoid &operator+=(const ProductMonoid other) {
		value *= other.value;
		return *this;
	}
};

template <class S> struct AffineMonoid {
	S a;
	S b;
	AffineMonoid(S A, S B) : a(A), b(B) {}
	AffineMonoid() : a(S{1}), b(S{0}) {}
	AffineMonoid operator+(const AffineMonoid other) const {
		return {a * other.a, a * other.b + b};
	}
	AffineMonoid &operator+=(const AffineMonoid other) {
		b += a * other.b;
		a *= other.a;
		return *this;
	}
};

template <class T, T (*sum)(T, T), T (*zero)()> class MonoidOf {
	T value;
	MonoidOf(T val) : value(val) {}
	MonoidOf() : value(zero()) {}
	MonoidOf operator+(const MonoidOf other) const {
		return sum(value, other.value);
	}
	MonoidOf &operator+=(const MonoidOf other) {
		value = sum(value, other.value);
		return *this;
	}
};

template <class T>
	requires numeric::Integral<T>
struct XorGroup {
	T value;
	XorGroup() : value(T{0}) {}
	XorGroup(T val) : value(val) {}
	XorGroup operator+(const XorGroup other) const {
		return value ^ other.value;
	}
	XorGroup &operator+=(const XorGroup other) {
		value ^= other.value;
		return *this;
	}
	XorGroup operator-() const { return *this; }
	XorGroup operator-(const XorGroup other) const {
		return value ^ other.value;
	}
	XorGroup &operator-=(const XorGroup other) {
		value ^= other.value;
		return *this;
	}
};

static_assert(internal::traits::Monoid<MaxMonoid<int>>);
static_assert(internal::traits::Monoid<MinMonoid<int>>);
static_assert(internal::traits::Monoid<GcdMonoid<int>>);
static_assert(internal::traits::Monoid<LcmMonoid<int>>);
static_assert(internal::traits::Monoid<ProductMonoid<int>>);
static_assert(internal::traits::Group<XorGroup<int>>);
static_assert(internal::traits::Monoid<AffineMonoid<int>>);

}; // namespace traits

}; // namespace mo::internal::utils

#endif
