#ifndef _MO_INTERNAL_DSU_HPP_
#define _MO_INTERNAL_DSU_HPP_

#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

namespace mo::internal {

struct DSU {
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n) : parent(n + 1), size(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int root(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = root(parent[x]);
    }

    bool join(int x, int y) {
        assert(1 <= x && x < parent.size());
        assert(1 <= y && y < parent.size());
        x = root(x);
        y = root(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            std::swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

    bool same(int x, int y) {
        assert(1 <= x && x < parent.size());
        assert(1 <= y && y < parent.size());
        return root(x) == root(y);
    }
};

}; // namespace mo::internal

#endif
