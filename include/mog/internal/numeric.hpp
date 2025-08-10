#ifndef _MOG_INTERNAL_NUMERIC_HPP_
#define _MOG_INTERNAL_NUMERIC_HPP_

#include <bit>
#include <type_traits>

namespace mog::internal::numeric {

template <typename Int>
concept Integral = std::is_integral_v<Int> || std::is_same_v<Int, __int128>;

using u64 = unsigned long long;

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
	return std::popcount(static_cast<u64>(x));
}

template <typename Int>
	requires std::is_integral_v<Int>
constexpr inline int bitWidth(Int x) {
	return std::bit_width(static_cast<u64>(x));
}

/**
 * returns floor(log2(x))
 */
template <typename Int>
	requires std::is_integral_v<Int>
constexpr inline int log2(Int x) {
	return bitWidth(x) - 1;
}

/**
 * returns floor(sqrt(x)).
 * assumes x >= 0.
 */
template <Integral Int> constexpr inline Int isqrt(Int x) {
	assert(x >= 0);
	if (x <= 1) {
		return x;
	}
	Int l = 1;
	Int r = x;
	while (r - l > 0) {
		Int m = l + (r - l) / 2;
		if (m <= x / m) {
			l = m;
		} else {
			r = m;
		}
	}
	return l;
}

}; // namespace mog::internal::numeric

#endif
