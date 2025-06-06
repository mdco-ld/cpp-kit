#ifndef _MO_INTERNAL_FENWICK_TREE_HPP_
#define _MO_INTERNAL_FENWICK_TREE_HPP_

#include <mo/internal/concepts/group.hpp>
#include <mo/internal/concepts/monoid.hpp>
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
    FenwickTree(int n) : t(n + 1, S{}), val(n + 1, S{}), n(n) {}

    /**
     * changes the value at position `i` to `val`.
     */
    void set(int i, S value)
        requires traits::Group<S>
    {
        add(i, value - val[i]);
    }

    /**
     * Adds the value `val` at position i;
     */
    void add(int i, S val) {
        val[i] += val;
        for (; i <= n; i += i & -i) {
            t[i] += val;
        }
    }

    /**
     * Sum of values in the range(
     */
    S sum(int r) {
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
        return sum(r) - sum(l - 1);
    }

    S operator[](std::size_t i) { return val[i]; }

  private:
    std::vector<S> t;
    std::vector<S> val;
    int n;
};

}; // namespace mo::internal

#endif
