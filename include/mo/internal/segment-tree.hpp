#ifndef _MO_INTERNAL_SEGMENT_TREE_HPP_
#define _MO_INTERNAL_SEGMENT_TREE_HPP_

#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/concepts/semigroup.hpp>
#include <vector>

namespace mo::internal {

/**
 * Segment tree
 * S must be a semigroup on the operator+
 */
template <traits::Semigroup S> class SegmentTree {
  public:
    /**
     * Build a segment tree with `n` elements.
     * The elements are initialized as the neutral element in S.
     */
    void build(int n)
        requires traits::Monoid<S>
    {
        t.assign(2 * n, S{});
		this->n = n;
    }

    /**
     * Build a segment tree with the elements of a vector
     */
    void build(std::vector<int> &from) {
        n = from.size();
        build(n);
        std::copy(from.begin(), from.end(), t.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    /**
     * Computes the sum of the elements in the interval `[l, r)` from left to
     * right.
     */
    S sum(int l, int r) requires traits::Monoid<S> {
        S accl, accr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                accl += t[l++];
            }
            if (r & 1) {
                accr += t[--r];
            }
        }
        return accl + accr;
    }

    /**
     * Changes the value at the position `i`.
     */
    void set(int i, S value) {
        t[i += n] = value;
        for (i >>= 1; i > 0; i >>= 1) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

	S get(int i) {
		return t[i + n];
	}

  private:
    std::vector<S> t;
    int n;
};

}; // namespace mo::internal

#endif
