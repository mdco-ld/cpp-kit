#ifndef _MO_INTERNAL_ZETA_HPP_
#define _MO_INTERNAL_ZETA_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/enumerate-primes.hpp>

#include <vector>

namespace mo::internal::zeta {

/**
 * Calculates the sum of the values of all subsets of M for every bitmask M.
 * Assumes S is a commutative monoid.
 */
template <traits::Monoid S> void subsetZeta(std::vector<S> &v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1) {
        for (int i = 1; i < n; i++) {
            if (i & j) {
                v[i] += v[i ^ j];
            }
        }
    }
}

/**
 * Finds every mask M given the sums of subsets.
 * Assumes S is a commutative group.
 */
template <traits::Group S> void subsetMobius(std::vector<S> &v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1) {
        for (int i = 1; i < n; i++) {
            if (i & j) {
                v[i] -= v[i ^ j];
            }
        }
    }
}

/**
 * Calculates the sum of the values of all supersets of M for every bitmask M.
 * Assumes S is a commutative monoid.
 */
template <traits::Monoid S> void supersetZeta(std::vector<S> &v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1) {
        for (int i = 1; i < n; i++) {
            if (i & j) {
                v[i ^ j] += v[i];
            }
        }
    }
}

/**
 * Finds every mask M given the sums of supersets.
 * Assumes S is a commutative group.
 */
template <traits::Group S> void supersetMobius(std::vector<S> &v) {
    int n = v.size();
    for (int j = 1; j < n; j <<= 1) {
        for (int i = 1; i < n; i++) {
            if (i & j) {
                v[i ^ j] -= v[i];
            }
        }
    }
}

/**
 * Calculates the sum of the values of all divisors of N for every number N.
 * Assumes S is a commutative monoid.
 */
template <traits::Monoid T> void divisorZeta(std::vector<T> &v) {
    int n = v.size();
    for (int p : sieve::enumeratePrimes(n)) {
        for (int i = 1; i * p < n; i++) {
            v[i * p] += v[i];
        }
    }
}

/**
 * Finds the value of every number N given the sums of values of divisors.
 * Assumes S is a commutative group.
 */
template <traits::Group T> void divisorMobius(std::vector<T> &v) {
    int n = v.size();
    for (int p : sieve::enumeratePrimes(n)) {
        for (int i = n / p; i > 0; i--) {
            v[i * p] -= v[i];
        }
    }
}

/**
 * Calculates the sum of the values of all multiples of N for every number N.
 * Assumes S is a commutative monoid.
 */
template <traits::Monoid T> void multipleZeta(std::vector<T> &v) {
    int n = v.size();
    for (int p : sieve::enumeratePrimes(n)) {
        for (int i = n / p; i > 0; i--) {
            v[i] += v[i * p];
        }
    }
}

/**
 * Finds the value of every number N given the sums of values of multiples.
 * Assumes S is a commutative group.
 */
template <traits::Group T> void multipleMobius(std::vector<T> &v) {
    int n = v.size();
    for (int p : sieve::enumeratePrimes(n)) {
        for (int i = 1; i * p < n; i++) {
            v[i] -= v[i * p];
        }
    }
}

}; // namespace mo::internal::zeta

#endif
