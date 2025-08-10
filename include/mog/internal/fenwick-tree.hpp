#ifndef _MOG_INTERNAL_FENWICK_TREE_HPP_
#define _MOG_INTERNAL_FENWICK_TREE_HPP_

#include <mog/internal/concepts/group.hpp>
#include <mog/internal/concepts/monoid.hpp>
#include <mog/internal/numeric.hpp>
#include <vector>

namespace mog::internal {

/**
 * Fenwick tree on group S.
 */
template <traits::Monoid S> class FenwickTree {
  public:
	/**
	 * Builds a fenwick tree filled with the neutral element of the group S.
	 */
	FenwickTree(int N) : t(N, S{}), val(N, S{}), n(N) {}

	/**
	 * changes the value at position `i` to `val`.
	 */
	void set(int i, S value)
		requires traits::Group<S>
	{
		add(i, value - val[i - 1]);
	}

	/**
	 * Adds the value `value` at position i.
	 */
	void add(int i, S value) {
		val[i - 1] += value;
		for (; i <= n; i += i & -i) {
			t[i - 1] += value;
		}
	}

	/**
	 * Sum of values in the prefix `[1, r]`.
	 */
	S prefixSum(int r) {
		S s{};
		for (; r > 0; r -= r & -r) {
			s += t[r - 1];
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
	int bisect(auto pred) {
		int k = 0;
		S acc{};
		for (int i = numeric::bitWidth(n) - 1; i >= 0; i--) {
			if (k + (1 << i) > n) {
				continue;
			}
			if (pred(acc + t[k + (1 << i)])) {
				k += 1 << i;
				acc += t[k];
			}
		}
		return k;
	}

	S operator[](std::size_t i) { return val[i - 1]; }

	inline int size() { return n; }

  private:
	std::vector<S> t;
	std::vector<S> val;
	int n;
};

}; // namespace mog::internal

#endif
