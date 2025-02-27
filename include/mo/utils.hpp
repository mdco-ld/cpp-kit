#ifndef _MO_UTILS_HPP_
#define _MO_UTILS_HPP_

#define makefn(fn) [](auto... args) { return fn(args...); }
#define constfn(val) []() -> decltype(val) { return val; }
#define nop() [](auto...) {}

namespace mo {

struct Range {
    int l;
    int r;

    inline int mid() { return l + (r - l) / 2; }
};

}; // namespace mo

#endif
