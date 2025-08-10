#ifndef _MOG_INTERNAL_BIT_CONVOLUTION_HPP_
#define _MOG_INTERNAL_BIT_CONVOLUTION_HPP_

#include <cassert>
#include <mog/internal/concepts/group.hpp>
#include <mog/internal/zeta.hpp>
#include <span>
#include <vector>

namespace mog::internal {

template <traits::Group T>
std::vector<T> convolutionAnd(std::vector<T> a, std::vector<T> b) {
	assert(a.size() == b.size());
	supersetFastZeta(a);
	supersetFastZeta(b);
	size_t n = a.size();
	for (size_t i = 0; i < n; i++) {
		a[i] *= b[i];
	}
	supersetFastMobius(a);
	return a;
}

template <traits::Group T>
std::vector<T> convolutionOr(std::vector<T> a, std::vector<T> b) {
	assert(a.size() == b.size());
	subsetFastZeta(a);
	subsetFastZeta(b);
	size_t n = a.size();
	for (size_t i = 0; i < n; i++) {
		a[i] *= b[i];
	}
	subsetFastMobius(a);
	return a;
}

template <traits::Group T>
std::vector<T> convolutionXorR(std::span<T> a, std::span<T> b) {
	assert(a.size() == b.size());
	size_t n = a.size();
	assert((n & (n - 1)) == 0); // power of 2
	std::vector<T> result(n);
	if (n == 2) {
		result[0] = a[0] * b[0] + a[1] * b[1];
		result[1] = a[0] * b[1] + a[1] * b[0];
		return result;
	}
	std::vector<T> ca0(n / 2);
	std::vector<T> cb0(n / 2);
	std::vector<T> ca1(n / 2);
	std::vector<T> cb1(n / 2);
	for (size_t i = 0; i < n / 2; i++) {
		ca0[i] = a[i] + a[i + n / 2];
		ca1[i] = a[i] - a[i + n / 2];
		cb0[i] = b[i] + b[i + n / 2];
		cb1[i] = b[i] - b[i + n / 2];
	}
	std::vector<T> c0 = convolutionXorR(std::span(ca0), std::span(cb0));
	std::vector<T> c1 = convolutionXorR(std::span(ca1), std::span(cb1));
	for (size_t i = 0; i < n / 2; i++) {
		result[i] = (c0[i] + c1[i]) / 2;
		result[i + n / 2] = (c0[i] - c1[i]) / 2;
	}
	return result;
}

template <traits::Group T>
std::vector<T> convolutionXor(std::vector<T> a, std::vector<T> b) {
	assert(a.size() == b.size());
	size_t n = a.size();
	assert((n & (n - 1)) == 0); // power of 2
	std::vector<T> result(n);
	for (size_t m = n >> 1; m > 0; m >>= 1) {
		for (size_t i = 0; i < n; i += m << 1) {
			for (size_t j = 0; j < m; j++) {
				T x = a[i + j];
				T y = a[i + j + m];
				a[i + j] = x + y;
				a[i + j + m] = x - y;
			}
		}
	}
	for (size_t m = n >> 1; m > 0; m >>= 1) {
		for (size_t i = 0; i < n; i += m << 1) {
			for (size_t j = 0; j < m; j++) {
				T x = b[i + j];
				T y = b[i + j + m];
				b[i + j] = x + y;
				b[i + j + m] = x - y;
			}
		}
	}
	for (size_t i = 0; i < n; i++) {
		result[i] = a[i] * b[i];
	}
	for (size_t m = 1; m < n; m <<= 1) {
		for (size_t i = 0; i < n; i += m << 1) {
			for (size_t j = 0; j < m; j++) {
				T x = result[i + j];
				T y = result[i + j + m];
				result[i + j] = x + y;
				result[i + j + m] = x - y;
			}
		}
	}
	for (size_t i = 0; i < n; i++) {
		result[i] = result[i] / n;
	}
	return result;
}

}; // namespace mog::internal

#endif
