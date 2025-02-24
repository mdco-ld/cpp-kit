#ifndef _MO_SPARSE_TABLE_
#define _MO_SPARSE_TABLE_

#include <cassert>
#include <vector>
#include <mo/utils.hpp>

namespace mo {

template <class T, T (*op)(T, T)> struct SparseTable {
    std::vector<std::vector<T>> st;
    int k;
    int n;
    SparseTable(std::vector<T> &v) {
        assert(v.size() > 0);
        k = std::__bit_width(v.size()) - 1;
        n = v.size();
        st.assign(k + 1, std::vector<T>(v.size()));
        copy(v.begin(), v.end(), st[0].begin());
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int L, int R) {
        assert(L <= R);
        int l = std::__bit_width(R - L + 1) - 1;
        return op(st[l][L], st[l][R - (1 << l) + 1]);
    }
};

}; // namespace MO

#endif
