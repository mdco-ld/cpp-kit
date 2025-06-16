#ifndef _MO_TREE_LCA_HPP_
#define _MO_TREE_LCA_HPP_

#include <mo/tree/tree.hpp>
#include <mo/sparse-table.hpp>

#include <functional>

namespace mo {

namespace tree {

template <typename T, bool oneBased> class LCA {
  private:
    const Tree<T, oneBased> &t;
    T r;
    std::vector<int64_t> lcaTin;
    std::vector<int64_t> lcaTout;
    MinSparseTable<std::pair<int64_t, T>> lcaArray;

    void prepareLCA() {
        lcaTin.assign(t.size() + oneBased, 0);
        lcaTout.assign(t.size() + oneBased, 0);
        std::vector<std::pair<int64_t, T>> eulerTour;
        int64_t t = 0;
        int64_t depth = 0;
        std::function<void(T, T)> dfs = [&](T v, T par) {
            depth++;
            eulerTour.emplace_back(depth, v);
            lcaTin[v] = t++;
            for (T u : this->t[v]) {
                if (u == par) {
                    continue;
                }
                dfs(u, v);
                eulerTour.emplace_back(depth, v);
                lcaTout[v] = t++;
            }
            lcaTout[v] = std::max(lcaTout[v], lcaTin[v]);
            depth--;
        };
        if constexpr (oneBased) {
            dfs(r, T{0});
        } else {
            dfs(r, T{this->t.size()});
        }
        lcaArray.build(eulerTour);
    }

  public:
    LCA(const Tree<T, oneBased> &tree, T root) : t(tree), r(root) { prepareLCA(); }

    T operator()(T u, T v) {
        return lcaArray
            .query(std::min(lcaTin[u], lcaTin[v]),
                   std::max(lcaTout[u], lcaTout[v]))
            .second;
    }
};

}; // namespace tree

}; // namespace mo

#endif
