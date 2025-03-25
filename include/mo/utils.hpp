#ifndef _MO_UTILS_HPP_
#define _MO_UTILS_HPP_

#include <cstdint>

#define makefn(fn) [](auto... args) { return fn(args...); }
#define constfn(val) []() -> decltype(val) { return val; }
#define nop() [](auto...) {}

namespace mo {

struct Interval {
    int64_t l;
    int64_t r;

    inline int64_t mid() const { return l + (r - l) / 2; }
    inline int64_t size() const { return r - l + 1; }
    inline bool isEmpty() const { return size() <= 0; }
    inline Interval left() const { return {l, mid()}; }
    inline Interval right() const { return {mid() + 1, r}; }
    inline bool isDisjoint(const Interval &other) const {
        return isEmpty() || other.isEmpty() || l > other.r || r < other.l;
    }
    inline bool contains(const Interval &other) const {
        return !isEmpty() && (other.isEmpty() || l <= other.l && r >= other.r);
    }
    inline bool contains(int64_t value) { return l <= value && value <= r; }
};

}; // namespace mo

#endif
