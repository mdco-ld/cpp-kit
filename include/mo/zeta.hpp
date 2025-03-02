#ifndef _MO_ZETA_HPP_
#define _MO_ZETA_HPP_

#include <cstddef>
#include <cstdint>
#include <vector>
#include <cassert>

namespace mo {

template <typename T> void subsetFastZeta(std::vector<T> &v) {
    size_t n = v.size();
    for (int64_t j = 1; j < n; j <<= 1) {
        for (int64_t i = 1; i < n; i++) {
            if (i & j) {
                v[i] += v[i ^ j];
            }
        }
    }
}

template <typename T> void subsetFastMobius(std::vector<T> &v) {
    size_t n = v.size();
    for (int64_t j = 1; j < n; j <<= 1) {
        for (int64_t i = 1; i < n; i++) {
            if (i & j) {
                v[i] -= v[i ^ j];
            }
        }
    }
}

template <typename T> void supersetFastZeta(std::vector<T> &v) {
    size_t n = v.size();
	assert(!(n & (n - 1)));
    for (int64_t j = 1; j < n; j <<= 1) {
        for (int64_t i = 1; i < n; i++) {
            if (i & j) {
                v[i ^ j] += v[i];
            }
        }
    }
}

template <typename T> void supersetFastMobius(std::vector<T> &v) {
    size_t n = v.size();
    for (int64_t j = 1; j < n; j <<= 1) {
        for (int64_t i = 1; i < n; i++) {
            if (i & j) {
                v[i ^ j] += v[i];
            }
        }
    }
}

}; // namespace mo

#endif
