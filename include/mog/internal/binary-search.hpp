#ifndef _MOG_INTERNAL_BINARY_SEARCH_HPP_
#define _MOG_INTERNAL_BINARY_SEARCH_HPP_

#include <type_traits>

namespace mog::internal {

template <class T>
	requires std::is_integral_v<T>
void binarySearch(T &l, T &r, auto f) {
	while (r - l > 1) {
		T m = l + (r - l) / 2;
		if (f(m)) {
			r = m;
		} else {
			l = m;
		}
	}
}

template <class T>
	requires std::is_integral_v<T>
void binarySearch(T &l, T &r, T step, auto f) {
	if (step == 1) {
		binarySearch(l, r, f);
		return;
	}
	T L = 0;
	T R = (r - l + step - 1) / step;
	while (R - L > 1) {
		T m = L + (R - L) / 2;
		if (f(l + m * step)) {
			R = m;
		} else {
			L = m;
		}
	}
	r = l + R * step;
	l += L * step;
}

}; // namespace mog::internal

#endif
