#ifndef _MOG_BINARY_SEARCH_HPP_
#define _MOG_BINARY_SEARCH_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/binary-search.hpp>

namespace mog {

template <class T>
	requires std::is_integral_v<T>
inline void bs(T &l, T &r, auto f) {
	if (l > r) {
		swap(l, r);
		auto f_ = [&](T i) -> bool { return !f(i); };
		mog::internal::binarySearch(l, r, f_);
	} else {
		mog::internal::binarySearch(l, r, f);
	}
}

template <class T>
	requires std::is_integral_v<T>
inline void bs(T &l, T &r, T step, auto f) {
	if (l > r) {
		swap(l, r);
		auto f_ = [&](T i) -> bool { return !f(i); };
		mog::internal::binarySearch(l, r, step, f_);
	} else {
		mog::internal::binarySearch(l, r, step, f);
	}
}

}; // namespace mog

#endif
