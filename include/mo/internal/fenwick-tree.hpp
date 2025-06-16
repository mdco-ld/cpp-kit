#ifndef _MO_INTERNAL_FENWICK_TREE_HPP_
#define _MO_INTERNAL_FENWICK_TREE_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/numeric.hpp>
#include <vector>

namespace mo::internal {

/**
 * Fenwick tree on group S.
 */
template <traits::Monoid S> class FenwickTree {
  public:
    /**
     * Builds a fenwick tree filled with the neutral element of the group S.
     */
    FenwickTree(int N) : t(N + 1, S{}), val(N + 1, S{}), n(N) {}

    /**
     * changes the value at position `i` to `val`.
     */
    void set(int i, S value)
        requires traits::Group<S>
    {
        add(i, value - val[i]);
    }

    /**
     * Adds the value `value` at position i.
     */
    void add(int i, S value) {
        val[i] += value;
        for (; i <= n; i += i & -i) {
            t[i] += value;
        }
    }

    /**
     * Sum of values in the prefix `[1, r]`.
     */
    S prefixSum(int r) {
        S s{};
        for (; r > 0; r -= r & -r) {
            s += t[r];
        }
        return s;
    }

    /**
     * Sum of values in the range `[l, r]`.
     */
    S sum(int l, int r)
        requires traits::Group<S>
    {
        return prefixSum(r) - prefixSum(l - 1);
    }

	/**
	 * Finds the largest prefix that is less than value.
	 * Uses operator<(S, S).
	 * `O(log(N))`
	 */
	int bisect(S value) {
		int k = 0;
		S acc{};
		for (int i = numeric::bitWidth(n) - 1; i >= 0; i--) {
			if (k + (1 << i) > n) {
				continue;
			}
			if (acc + t[k + (1 << i)] < value) {
				k += 1 << i;
				acc += t[k];
			}
		}
		return k;
	}

	/**
	 * Finds largest prefix that satisfies some condition.
	 * Assumes the prefixes of the tree are partitioned by f at some point.
	 * `O(log(N))`
	 */
	int bisect(auto f) {
		int k = 0;
		S acc{};
		for (int i = numeric::bitWidth(n) - 1; i >= 0; i--) {
			if (k + (1 << i) > n) {
				continue;
			}
			if (f(acc + t[k + (1 << i)])) {
				k += 1 << i;
				acc += t[k];
			}
		}
		return k;
	}

    S operator[](std::size_t i) { return val[i]; }

  private:
    std::vector<S> t;
    std::vector<S> val;
    int n;
};

}; // namespace mo::internal

#endif
