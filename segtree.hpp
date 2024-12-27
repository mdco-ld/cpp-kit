#ifndef _MO_SEGTREE_
#define _MO_SEGTREE_

#include <vector>

namespace MO {

namespace ds {

template <class T, T (*op)(T, T), T (*e)()> struct SegmentTree {
    std::vector<T> t;
    int n;
    SegmentTree(int N) : n(N), t(2 * N, e()) {}
    void build(std::vector<T> &v) {
        copy(v.begin(), v.end(), t.begin() + n);
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

}; // namespace ds

}; // namespace MO

#endif
