#ifndef _MO_BINARY_SEARCH_HPP_
#define _MO_BINARY_SEARCH_HPP_

#include <type_traits>

namespace mo {

template <typename T>
    requires(std::is_integral<T>::value)
void bs(T &l, T &r, auto f) {
    while (r - l > 1) {
        T mid = l + (r - l) / 2;
        if (f(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
}

template <typename T>
    requires(std::is_integral<T>::value)
void bs(T &l, T &r, T step, auto f) {
    assert((r - l) % step == 0);
    int base = l;
    l = 0;
    r -= base;
    r /= step;
    while (r - l > 1) {
        T mid = l + (r - l) / 2;
        if (f(base + mid * step)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    l = step * l + base;
    r = step * r + base;
}

}; // namespace mo

#endif
