#ifndef _MOG_INTERNAL_UTILS_HPP_
#define _MOG_INTERNAL_UTILS_HPP_

#include <mog/internal/concepts/group.hpp>
#include <mog/internal/concepts/monoid.hpp>
#include <mog/internal/concepts/semigroup.hpp>
#include <mog/internal/concepts/semiring.hpp>
#include <mog/internal/numeric.hpp>

#include <algorithm>
#include <limits>
#include <tuple>
#include <utility>

namespace mog::internal::utils {

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
	template <class U>
	MaxMonoid(U val)
		requires std::constructible_from<T, U>
		: value(val) {}
	MaxMonoid operator+(const MaxMonoid other) const {
		return std::max(value, other.value);
	}
	MaxMonoid &operator+=(const MaxMonoid other) {
		value = std::max(value, other.value);
		return *this;
	}
};

template <class T> struct MinMonoid {
	T value;
	MinMonoid() : value(limits<T>::maxValue()) {}
	MinMonoid(T val) : value(val) {}
	template <class U>
	MinMonoid(U val)
		requires std::constructible_from<T, U>
		: value(val) {}
	MinMonoid operator+(const MinMonoid other) const {
		return std::min(value, other.value);
	}
	MinMonoid &operator+=(const MinMonoid other) {
		value = std::min(value, other.value);
		return *this;
	}
};

template <class T> struct MinCntMonoid {
	T value;
	int cnt;
	MinCntMonoid() : value(limits<T>::maxValue()), cnt(0) {}
	MinCntMonoid(T val) : value(val), cnt(1) {}
	MinCntMonoid(T val, int count) : value(val), cnt(count) {}
	template <class U>
	MinCntMonoid(U val)
		requires std::constructible_from<T, U>
		: value(val), cnt(1) {}
	MinCntMonoid operator+(const MinCntMonoid other) const {
		if (value == other.value) {
			return MinCntMonoid{value, cnt + other.cnt};
		}
		if (value < other.value) {
			return *this;
		}
		return other;
	}
	MinCntMonoid &operator+=(const MinCntMonoid other) {
		if (other.value < value) {
			*this = other;
			return *this;
		}
		if (value < other.value) {
			return *this;
		}
		cnt += other.cnt;
		return *this;
	}
};

template <class T> struct MaxCntMonoid {
	T value;
	int cnt;
	MaxCntMonoid() : value(limits<T>::minValue()), cnt(0) {}
	MaxCntMonoid(T val) : value(val), cnt(1) {}
	MaxCntMonoid(T val, int count) : value(val), cnt(count) {}
	template <class U>
	MaxCntMonoid(U val)
		requires std::constructible_from<T, U>
		: value(val), cnt(1) {}
	MaxCntMonoid operator+(const MaxCntMonoid other) const {
		if (value == other.value) {
			return {value, cnt + other.cnt};
		}
		if (other.value < value) {
			return *this;
		}
		return other;
	}
	MaxCntMonoid &operator+=(const MaxCntMonoid other) {
		if (value < other.value) {
			*this = other;
			return *this;
		}
		if (other.value < value) {
			return *this;
		}
		cnt += other.cnt;
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
		requires internal::traits::Semiring<T>
		: value(T{1}) {}
	ProductMonoid()
		requires(!internal::traits::Semiring<T>)
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

template< class T>
requires numeric::Integral<T>
struct OrMonoid {
	T value;
	OrMonoid() : value(T{0}) {}
	OrMonoid(T val) : value(val) {}
	OrMonoid operator+(const OrMonoid other) const {
		return value | other.value;
	}
	OrMonoid &operator+=(const OrMonoid other) {
		value |= other.value;
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

template <internal::traits::Monoid S> struct ReverseMonoid {
	S value;
	ReverseMonoid() : value() {}
	ReverseMonoid(S val) : value(val) {}
	template <class U>
	ReverseMonoid(U val)
		requires std::constructible_from<S, U>
		: value(val) {}
	ReverseMonoid operator+(const ReverseMonoid other) const {
		return other.value + value;
	}
	ReverseMonoid &operator+=(const ReverseMonoid other) {
		value = other.value + value;
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
static_assert(internal::traits::Monoid<ReverseMonoid<int>>);

}; // namespace traits

}; // namespace mog::internal::utils

#endif
