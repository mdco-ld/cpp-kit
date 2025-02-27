#ifndef _MO_TREE_HPP_
#define _MO_TREE_HPP_

#include <functional>
#include <vector>

namespace mo {

template<typename T>
class Tour {
  private:
    std::vector<int> tin;
    std::vector<int> tout;

  public:
    Tour(std::vector<int> &&tin, std::vector<int> &&tout)
        : tin(tin), tout(tout) {}

    inline int inTimeOf(T u) { return tin[u]; }

    inline int outTimeOf(T u) { return tout[u]; }
};

template<typename T>
class Tree {
  private:
    std::vector<std::vector<T>> edges;
    int n;

  public:
    Tree(int n) : n(n), edges(n + 1) {}

    void addEdge(T u, T v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void dfsFrom(T root, std::function<void(T)> inCallback) {
        std::function<void(T, T)> dfs = [&](T u, T parent) {
            inCallback(u);
            for (int v : edges[u]) {
                if (v == parent) {
                    continue;
                }
                dfs(v, u);
            }
        };
    }

    void dfsFrom(T root, std::function<void(T)> inCallback,
                 std::function<void(T)> outCallback) {
        std::function<void(T, T)> dfs = [&](T u, T parent) {
            inCallback(u);
            for (T v : edges[u]) {
                if (v == parent) {
                    continue;
                }
            }
            outCallback(u);
        };
        dfs(root, -1);
    }

    void dfsFrom(T root, std::function<void(T)> inCallback,
                 std::function<void(T)> outCallback,
                 std::function<void(T)> midCallback) {
        std::function<void(T, T)> dfs = [&](T u, T parent) {
            inCallback(u);
            for (T v : edges[u]) {
                if (v == parent) {
                    continue;
                }
                dfs(v, u);
                midCallback(u);
            }
            outCallback(u);
        };
        dfs(root, -1);
    }

    Tour<T> tourFrom(T root) {
        std::vector<T> tin(n);
        std::vector<T> tout(n);
        int time = 0;
        dfsFrom(
            root, [&](T u) { tin[u] = time++; },
            [&](T u) { tout[u] = time++; });
        return Tour(std::move(tin), std::move(tout));
    }

    Tour<T> tourFrom(T root, std::function<void(T)> inCallback,
                  std::function<void(T)> outCallback) {
        std::vector<T> tin(n);
        std::vector<T> tout(n);
        int time = 0;
        dfsFrom(
            root,
            [&](T u) {
                tin[u] = time++;
                inCallback(u);
            },
            [&](T u) {
                tout[u] = time++;
                outCallback(u);
            });
        return Tour<T>(std::move(tin), std::move(tout));
    }
};

}; // namespace mo

#endif
