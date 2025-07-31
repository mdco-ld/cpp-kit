#ifndef _MO_BINARY_SEARCH_HPP_
#define _MO_BINARY_SEARCH_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/binary-search.hpp>

namespace mo {

template <class T>
    requires std::is_integral_v<T>
inline void bs(T &l, T &r, auto f) {
    if (l > r) {
        swap(l, r);
        auto f_ = [&](T i) -> bool { return !f(i); };
        mo::internal::binarySearch(l, r, f_);
    } else {
        mo::internal::binarySearch(l, r, f);
    }
}

template <class T>
    requires std::is_integral_v<T>
inline void bs(T &l, T &r, T step, auto f) {
	if (l > r) {
		swap(l, r);
		auto f_ = [&](T i) -> bool { return !f(i); };
		mo::internal::binarySearch(l, r, step, f_);
	} else {
		mo::internal::binarySearch(l, r, step, f);
	}
}

}; // namespace mo

#endif
