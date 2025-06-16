#ifndef _MO_ZETA_HPP_
#define _MO_ZETA_HPP_

#include <mo/math/sieve.hpp>

#include <cstddef>
#include <cstdint>
#include <vector>

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

template <typename T> void divisorFastZeta(std::vector<T> &v) {
    size_t n = v.size();
    for (int p : math::getPrimes(n)) {
        for (int i = 1; i * p < n; i++) {
            v[i * p] += v[i];
        }
    }
}

template <typename T> void divisorFastMobius(std::vector<T> &v) {
    size_t n = v.size();
    for (int p : math::getPrimes(n)) {
        for (int i = n / p; i > 0; i--) {
            v[i * p] -= v[i];
        }
    }
}

template <typename T> void multipleFastZeta(std::vector<T> &v) {
    size_t n = v.size();
    for (int p : math::getPrimes(n)) {
        for (int i = n / p; i > 0; i--) {
            v[i] += v[i * p];
        }
    }
}

template <typename T> void multipleFastMobius(std::vector<T> &v) {
    size_t n = v.size();
    for (int p : math::getPrimes(n)) {
        for (int i = 1; i * p < n; i++) {
            v[i] -= v[i * p];
        }
    }
}

}; // namespace mo

#endif
