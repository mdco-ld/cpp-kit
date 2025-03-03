#ifndef _MO_BIT_CONVOLUTION_HPP_
#define _MO_BIT_CONVOLUTION_HPP_

#include <mo/zeta.hpp>
#include <vector>

namespace mo {

template <typename T>
std::vector<T> convolutionAnd(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    supersetFastZeta(a);
    supersetFastZeta(b);
    size_t n = a.size();
    for (int64_t i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    supersetFastMobius(a);
    return a;
}

template <typename T>
std::vector<T> convolutionOr(std::vector<T> a, std::vector<T> b) {
    assert(a.size() == b.size());
    subsetFastZeta(a);
    subsetFastZeta(b);
    size_t n = a.size();
    for (int64_t i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    subsetFastMobius(a);
    return a;
}

}; // namespace mo

#endif
