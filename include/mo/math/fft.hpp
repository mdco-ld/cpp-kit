#ifndef _MO_MATH_FFT_HPP_
#define _MO_MATH_FFT_HPP_

#include <mo/math/field.hpp>
#include <mo/math/modint.hpp>

#include <array>
#include <vector>

namespace mo {

namespace math {

namespace internal {

constexpr std::array<ModInt998244353, 24> getRoots() {
    int64_t baseRoot = 15311432;
    std::array<ModInt998244353, 24> roots;
    roots[23] = baseRoot;
    for (int i = 22; i >= 0; i--) {
        roots[i] = roots[i + 1] * roots[i + 1];
    }
    return roots;
}

static constexpr std::array<ModInt998244353, 24> roots = getRoots();

constexpr ModInt998244353 get2toNthRoot(int n) { return roots[n]; }

}; // namespace internal

template <Field F>
std::vector<typename F::ValueType> fft(std::vector<typename F::ValueType> v) {
	// TODO: Stop begin lazy and optimize this FFT
    using T = typename F::ValueType;
	using BaseType = typename F::BaseType;
    int m = v.size();
    if (m == 1) {
        return v;
    }
    T omega = F::zero();
    if constexpr (std::same_as<BaseType, ModInt998244353>) {
        omega = F::make(internal::get2toNthRoot(std::__bit_width(m) - 1));
    } else if constexpr (std::same_as<T, double>) {
        static_assert(false); // TODO: Implement this
    } else {
        static_assert(false);
    }
    std::vector<T> even(m / 2);
    std::vector<T> odd(m / 2);
    for (int i = 0; i < m / 2; i++) {
        even[i] = v[i << 1];
        odd[i] = v[i << 1 | 1];
    }
    even = fft<F>(even);
    odd = fft<F>(odd);
    T base = F::one();
    for (int i = 0; i < m / 2; i++) {
		v[i] = F::plus(even[i], F::mul(base, odd[i]));
		v[i + m / 2] = F::plus(even[i], F::mul(F::neg(base), odd[i]));
		base = F::mul(base, omega);
    }
    return v;
}

template<Field F>
std::vector<typename F::ValueType> convolution(std::vector<typename F::ValueType> a, std::vector<typename F::ValueType> b) {
	using T = typename F::ValueType;
	if (a.size() * b.size() < 100) {
		int m = a.size() + b.size() - 1;
		std::vector<T> result(m, F::zero());
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				result[i + j] = F::plus(result[i + j], F::mul(a[i], b[j]));
			}
		}
		return result;
	}
	int n = a.size();
	int m = b.size();
	int k = 1 << std::__bit_width(n + m - 1);
	if (n + m - 1 == (k >> 1)) {
		k >>= 1;
	}
	while (a.size() < k) {
		a.push_back(F::zero());
	}
	while (b.size() < k) {
		b.push_back(F::zero());
	}
	a = fft<F>(a);
	b = fft<F>(b);
	for (int i = 0; i < k; i++) {
		a[i] = F::mul(a[i], b[i]);
	}
	a = fft<F>(a);
	for (int i = 0; i < k; i++) {
		a[i] = F::mul(F::inv(T(k)), a[i]);
	}
	reverse(a.begin() + 1, a.end());
	a.resize(n + m - 1);
	return a;
}

}; // namespace math

}; // namespace mo

#endif
