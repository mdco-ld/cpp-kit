#ifndef _MO_LAZY_SEGTREE_HPP_
#define _MO_LAZY_SEGTREE_HPP_

#include <algorithm>
#include <vector>

#include <mo/utils.hpp>

namespace mo {

template <class T, T (*op)(T, T), T (*e)(), class U, T (*mapping)(U, T),
          U (*compose)(U, U), U (*id)()>
class LazySegtree {
  private:
    std::vector<T> t;
    std::vector<U> p;
    int n;

    inline void applyPoint(int i, U f) {
        t[i] = mapping(f, t[i]);
        if (i < n) {
            p[i] = compose(f, p[i]);
        }
    }

    void propagate(int i) {
        if (i >= n) {
            return;
        }
        applyPoint(i << 1, p[i]);
        applyPoint(i << 1 | 1, p[i]);
        p[i] = id();
    }

    inline void pullAll(int i) {
        int h = std::__bit_width(i) - 1;
        for (int j = h; j > 0; j--) {
            propagate(i >> j);
        }
    }

    inline void pushAll(int i) {
        for (i >>= 1; i > 0; i >>= 1) {
            t[i] = mapping(p[i], op(t[i << 1], t[i << 1 | 1]));
        }
    }

  public:
    LazySegtree() {}

    LazySegtree(int N) : t(2 * N, e()), p(N, id()), n(N) {
	}

    void build(std::vector<T> &v) {
        n = v.size();
        t.assign(2 * n, e());
        p.assign(n, id());
        std::copy(v.begin(), v.end(), t.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            t[i] = op(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int i, T value) {
        pullAll(i += n);
        t[i] = value;
        for (i >>= 1; i > 0; i >>= 1) {
            t[i] = op(t[i << 1], t[i << 1 | 1]);
        }
    }

    T get(int i) {
        pullAll(i + n);
        return t[i + n];
    }

    inline void apply(Interval interval, U f) {
        apply(interval.l, interval.r + 1, f);
    }

    void apply(int l, int r, U f) {
        int L = l += n;
        int R = r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                applyPoint(l++, f);
            }
            if (r & 1) {
                applyPoint(--r, f);
            }
        }
        pushAll(L);
        pushAll(R - 1);
    }

    inline T query(Interval interval) {
        return query(interval.l, interval.r + 1);
    }

    T query(int l, int r) {
        T accL = e();
        T accR = e();
        pullAll(l + n);
        pullAll(r + n - 1);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                accL = op(accL, t[l++]);
            }
            if (r & 1) {
                accR = op(t[--r], accR);
            }
        }
        return op(accL, accR);
    }
};

}; // namespace mo

#endif
