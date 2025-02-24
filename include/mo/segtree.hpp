#ifndef _MO_SEGMENT_TREE_HPP_
#define _MO_SEGMENT_TREE_HPP_

#include <vector>

#include <mo/utils.hpp>

namespace mo {

template <class T, T (*op)(T, T), T (*e)()> class SegmentTree {
  private:
    std::vector<T> t;
    int n;

  public:
    SegmentTree() : n(0) {}

    SegmentTree(int N) : n(N), t(2 * N, e()) {}

    void build(std::vector<T> &v) {
        n = v.size();
        t.clear();
        t.reserve(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            t.push_back(e());
        }
        std::copy(v.begin(), v.end(), t.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            t[i] = op(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int p, T value) {
        for (t[p += n] = value; p > 1; p >>= 1) {
            t[p >> 1] = op(t[p], t[p ^ 1]);
        }
    }

    void add(int p, T value) {
        p += n;
        for (t[p] = op(t[p], value); p > 1; p >>= 1) {
            t[p >> 1] = op(t[p], t[p ^ 1]);
        }
    }

    T query(int l, int r) {
        T accl = e();
        T accr = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                accl = op(accl, t[l++]);
            }
            if (r & 1) {
                accr = op(t[--r], accr);
            }
        }
        return op(accl, accr);
    }
};

template<typename T, T e>
using MaxSegtree = SegmentTree<T, makefn(max), constfn(e)>;

template<typename T, T e>
using MinSegtree = SegmentTree<T, makefn(min), constfn(e)>;

}; // namespace mo

#endif
