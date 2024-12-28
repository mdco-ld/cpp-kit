#ifndef _MO_MATH_
#define _MO_MATH_

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numbers>
#include <vector>
#include <complex>

namespace MO {

namespace math {

constexpr int DEFAULT_PRIME_MOD = 998244353;

constexpr bool isKnownPrime(int64_t number) {
    // TODO: Make this better
    return number == 2 || number == 3 || number == 5 || number == 7 ||
           number == DEFAULT_PRIME_MOD || number == 1000000007;
}

template <int64_t mod = DEFAULT_PRIME_MOD> class ModInt {

  public:
    ModInt() : ModInt(0) {}
    ModInt(int64_t val) {
        value = val;
        value %= mod;
        if (value < 0) {
            value += mod;
        }
    }
    int64_t val() { return value; }
    ModInt operator+(ModInt other) { return ModInt(value + other.value); }
    ModInt operator-(ModInt other) { return ModInt((value - other.value)); }
    ModInt operator*(ModInt other) { return ModInt(value * other.value); }
    ModInt &operator+=(ModInt other) {
        value += other.value;
        value %= mod;
        return *this;
    }
    ModInt &operator*=(ModInt other) {
        value *= other.value;
        value %= mod;
        return *this;
    }
    ModInt &operator-=(ModInt other) { return *this += mod - other.value; }
    bool operator==(ModInt other) { return value == other.value; }

    int64_t primeInverse(int64_t value) {
        return value <= 1 ? value
                          : mod - (int64_t)(mod / value) *
                                      primeInverse(mod % value) % mod;
    }

    ModInt inverse() {
        if constexpr (isKnownPrime(mod)) {
            return primeInverse(value);
        } else {
            // TODO: Unimplemented!!!
        }
    }

  private:
    int64_t value;
};

template <int64_t mod>
std::ostream &operator<<(std::ostream &out, ModInt<mod> value) {
    return out << value.val();
}

template <typename T> T getRoot(size_t r);

template <> inline ModInt<DEFAULT_PRIME_MOD> getRoot(size_t r) {
	r = std::__bit_width(r) - 1;
    static constexpr int64_t roots[] = {
        1,         998244352, 911660635, 372528824, 929031873, 452798380,
        922799308, 781712469, 476477967, 166035806, 258648936, 584193783,
        63912897,  350007156, 666702199, 968855178, 629671588, 24514907,
        996173970, 363395222, 565042129, 733596141, 267099868, 15311432};
    return roots[r];
}

template<> inline std::complex<double> getRoot<std::complex<double>>(size_t r) {
	double angle = 2 * std::numbers::pi / r;
	return std::complex<double>(std::cos(angle), std::sin(angle));
}

template<> inline std::complex<long double> getRoot<std::complex<long double>>(size_t r) {
	double angle = 2 * std::numbers::pi / r;
	return std::complex<long double>(std::cos(angle), std::sin(angle));
}

template<> inline std::complex<float> getRoot<std::complex<float>>(size_t r) {
	double angle = 2 * std::numbers::pi / r;
	return std::complex<float>(std::cos(angle), std::sin(angle));
}

template <int64_t mod> inline ModInt<mod> getInverse(ModInt<mod> val) {
    return val.inverse();
}

inline float getInverse(float val) {
	return 1.0 / val;
}

inline double getInverse(double val) {
	return 1.0 / val;
}

inline long double getInverse(long double val) {
	return 1.0 / val;
}

template <typename T> std::vector<T> fft(std::vector<T> a) {
    size_t m = a.size();
    if (m == 1) {
        return a;
    }
    std::vector<T> even(m / 2);
    std::vector<T> odd(m / 2);
    for (size_t i = 0; i < m; i += 2) {
        even[i / 2] = a[i];
    }
    for (size_t i = 1; i < m; i += 2) {
        odd[i / 2] = a[i];
    }
    even = fft(even);
    odd = fft(odd);
    std::vector<T> result(m);
    T omega = getRoot<T>(m);
    T om = 1;
    for (size_t i = 0; i < m / 2; i++) {
        result[i] = even[i] + om * odd[i];
        result[i + m / 2] = even[i] - om * odd[i];
        om *= omega;
    }
    return result;
}

template <typename T>
std::vector<T> convolution(std::vector<T> a, std::vector<T> b) {
    size_t m = a.size() + b.size();
    m = 1ll << (std::__bit_width(m));
    a.resize(m);
    b.resize(m);
    a = fft(a);
    b = fft(b);
    for (size_t i = 0; i < m; i++) {
        a[i] *= b[i];
    }
    a = fft(a);
    for (size_t i = 0; i < m; i++) {
        a[i] *= getInverse(T(m));
    }
    std::reverse(a.begin() + 1, a.end());
    return a;
}

template <typename T> class Poly {
  public:
    Poly() {}

    template <typename U>
    Poly(U val)
        requires std::constructible_from<T, U>
    {
        a.push_back(val);
    }

    template <typename U>
    Poly(std::initializer_list<U> vals)
        requires std::constructible_from<T, U>
    {
        for (U val : vals) {
            a.push_back(T(val));
        }
    }

    Poly(const Poly &other) { a = other.a; }

    size_t deg() { return a.size() ? a.size() - 1 : 0; }

    Poly &operator+=(const Poly &other) {
        if (a.size() < other.a.size()) {
            a.resize(other.a.size());
        }
        for (size_t i = 0; i < other.a.size(); i++) {
            a[i] += other.a[i];
        }
        return *this;
    }

    template <typename U>
    Poly &operator+=(U value)
        requires std::constructible_from<T, U>
    {
        T val = value;
        a[0] += val;
		return *this;
    }

    Poly &operator-=(const Poly &other) {
        if (a.size() < other.a.size()) {
            a.resize(other.a.size());
        }
        for (size_t i = 0; i < other.a.size(); i++) {
            a[i] -= other.a[i];
        }
		return *this;
    }

    Poly &operator*=(const Poly &other) {
		if (a.size() + other.a.size() < 129) {
			std::vector<T> result(a.size() + other.a.size() - 1);
			for (size_t i = 0; i < a.size(); i++) {
				for (size_t j = 0; j < other.a.size(); j++) {
					result[i + j] += a[i] * other.a[j];
				}
			}
			a = result;
		} else {
			a = convolution(a, other.a);
		}
        while (a.size() && a.back() == T{}) {
            a.pop_back();
        }
        return *this;
    }

    template <typename U>
    Poly &operator*=(U value)
        requires std::constructible_from<T, U>
    {
        T val = value;
        for (size_t i = 0; i < a.size(); i++) {
            a[i] *= val;
        }
        return *this;
    }

    Poly operator+(const Poly &other) {
        Poly result(*this);
        result += other;
        return result;
    }

    Poly operator-(const Poly &other) {
        Poly result(*this);
        result -= other;
        return result;
    }

    Poly operator*(const Poly &other) {
        Poly result(*this);
        result *= other;
        return result;
    }

    T operator()(T x) {
        T p = 1;
        T result = 0;
        for (size_t i = 0; i < a.size(); i++) {
            result += a[i] * p;
            p *= x;
        }
        return result;
    }

    T operator[](size_t idx) { return idx < a.size() ? a[idx] : T{}; }

    std::vector<T> &coefs() { return a; }

    Poly &operator<<(int64_t shift) {
        std::reverse(a.begin(), a.end());
        a.resize(a.size() + (size_t)shift);
        std::reverse(a.begin(), a.end());
        return *this;
    }

  private:
    std::vector<T> a;
};

template <typename T> std::ostream &operator<<(std::ostream &out, Poly<T> p) {
    out << "[";
	for (size_t i = 0; i <= p.deg(); i++) {
		out << p[i];
		if (i < p.deg()) {
			out << ", ";
		}
	}
	return out << "]";
}

} // namespace math

}; // namespace MO

#endif
