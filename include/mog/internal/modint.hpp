#ifndef _MO_INTERNAL_MODINT_HPP_
#define _MO_INTERNAL_MODINT_HPP_

#include <concepts>
#include <cstdint>
#include <tuple>

namespace mo::internal {

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

	constexpr inline ModInt operator+(ModInt other) const {
		return value + other.value;
	}
	constexpr inline ModInt operator-(ModInt other) const {
		return value - other.value;
	}
	constexpr inline ModInt operator*(ModInt other) const {
		return value * other.value;
	}
	constexpr inline ModInt operator/(ModInt other) const {
		return (*this) * other.inverse();
	}
	constexpr inline ModInt operator-() const { return -value; }
	constexpr inline int64_t toInt() const { return value; }
	constexpr ModInt inverse() const {
		int64_t x, y;
		extendedEuclid(value, MOD, x, y);
		return x;
	}

	inline ModInt &operator+=(ModInt other) {
		value += other.value;
		value %= MOD;
		return *this;
	}
	inline ModInt &operator*=(ModInt other) {
		value *= other.value;
		value %= MOD;
		return *this;
	}
	inline ModInt &operator-=(ModInt other) {
		value -= other.value;
		value %= MOD;
		if (value < 0) {
			value += MOD;
		}
		return *this;
	}
	inline ModInt &operator/=(ModInt other) {
		return *this = (*this) * other.inverse();
	}

	constexpr inline bool operator==(ModInt other) const {
		return value == other.value;
	}

	constexpr inline bool operator!=(ModInt other) const {
		return value != other.value;
	}

  private:
	int64_t value;
};

template <> class ModInt<2> {
  public:
	constexpr ModInt() : value(0) {}
	constexpr ModInt(int64_t x) {
		if (x < 0) {
			x = -x;
		}
		x &= 1;
		value = x;
	}

	constexpr inline ModInt operator+(ModInt other) {
		return value ^ other.value;
	}
	constexpr inline ModInt operator-(ModInt other) {
		return value ^ other.value;
	}
	constexpr inline ModInt operator*(ModInt other) {
		return value & other.value;
	}
	constexpr inline ModInt operator/(ModInt other) {
		return (*this) * other.inverse();
	}
	constexpr inline ModInt operator-() { return -value; }
	constexpr inline int64_t toInt() { return value; }
	constexpr inline ModInt inverse() { return value; }

	inline ModInt &operator+=(ModInt other) {
		value ^= other.value;
		return *this;
	}
	inline ModInt &operator*=(ModInt other) {
		value &= other.value;
		return *this;
	}
	inline ModInt &operator-=(ModInt other) {
		value ^= other.value;
		return *this;
	}
	inline ModInt &operator/=(ModInt other) {
		return *this = (*this) * other.inverse();
	}

	constexpr inline bool operator==(ModInt other) {
		return value == other.value;
	}

	constexpr inline bool operator!=(ModInt other) {
		return value != other.value;
	}

  private:
	int8_t value;
};

}; // namespace mo::internal

#endif
