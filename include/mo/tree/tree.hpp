#ifndef _MO_TREE_HPP_
#define _MO_TREE_HPP_

#include <cstdint>
#include <functional>
#include <vector>

namespace mo {

namespace tree {

template <typename T, bool oneBased = true> class Tree {
  private:
    std::vector<std::vector<T>> edges;
    int n;

  public:
    Tree(int n) : n(n), edges(n + oneBased) {}

    void addEdge(T u, T v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    std::vector<T> &operator[](T v) { return edges[v]; }

    inline int64_t size() { return n; }

    void preOrderDfs(T start, std::function<void(T, T)> visit) {
        std::function<void(T, T)> dfs_ = [&](T v, T par) {
            visit(v, par);
            for (T u : edges[v]) {
                if (u == par) {
                    continue;
                }
                dfs_(u, v);
            }
        };
        if constexpr (oneBased) {
            dfs_(start, T{0});
        } else {
            dfs_(start, T{n});
        }
    }

    void postOrderDfs(T start, std::function<void(T, T)> visit) {
        std::function<void(T, T)> dfs_ = [&](T v, T par) {
            for (T u : edges[v]) {
                if (u == par) {
                    continue;
                }
                dfs_(u, v);
            }
            visit(v, par);
        };
        if constexpr (oneBased) {
            dfs_(start, T{0});
        } else {
            dfs_(start, T{n});
        }
    }

    void dfs(T start, std::function<void(T, T)> visit) {
        std::function<void(T, T)> dfs_ = [&](T v, T par) {
            for (T u : edges[v]) {
                if (u == par) {
                    continue;
                }
                dfs_(u, v);
                visit(v, u);
            }
        };
        if constexpr (oneBased) {
            dfs_(start, T{0});
        } else {
            dfs_(start, T{n});
        }
    }
};

}; // namespace tree

}; // namespace mo

#endif
