#ifndef _MO_TREE_HPP_
#define _MO_TREE_HPP_

#include <functional>
#include <vector>

namespace mo {

class Tour {
  private:
    std::vector<int> tin;
    std::vector<int> tout;

  public:
    Tour(std::vector<int> &&tin, std::vector<int> &&tout)
        : tin(tin), tout(tout) {}

    inline int inTimeOf(int u) { return tin[u]; }

    inline int outTimeOf(int u) { return tout[u]; }
};

class Tree {
  private:
    std::vector<std::vector<int>> edges;
    int n;

  public:
    Tree(int n) : n(n), edges(n + 1) {}

    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void dfsFrom(int root, std::function<void(int)> inCallback) {
        std::function<void(int, int)> dfs = [&](int u, int parent) {
            inCallback(u);
            for (int v : edges[u]) {
                if (v == parent) {
                    continue;
                }
                dfs(v, u);
            }
        };
    }

    void dfsFrom(int root, std::function<void(int)> inCallback,
                 std::function<void(int)> outCallback) {
        std::function<void(int, int)> dfs = [&](int u, int parent) {
            inCallback(u);
            for (int v : edges[u]) {
                if (v == parent) {
                    continue;
                }
            }
            outCallback(u);
        };
        dfs(root, -1);
    }

    void dfsFrom(int root, std::function<void(int)> inCallback,
                 std::function<void(int)> outCallback,
                 std::function<void(int)> midCallback) {
        std::function<void(int, int)> dfs = [&](int u, int parent) {
            inCallback(u);
            for (int v : edges[u]) {
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

    Tour tourFrom(int root) {
        std::vector<int> tin(n);
        std::vector<int> tout(n);
        int time = 0;
        dfsFrom(
            root, [&](int u) { tin[u] = time++; },
            [&](int u) { tout[u] = time++; });
        return Tour(std::move(tin), std::move(tout));
    }

    Tour tourFrom(int root, std::function<void(int)> inCallback,
                  std::function<void(int)> outCallback) {
        std::vector<int> tin(n);
        std::vector<int> tout(n);
        int time = 0;
        dfsFrom(
            root,
            [&](int u) {
                tin[u] = time++;
                inCallback(u);
            },
            [&](int u) {
                tout[u] = time++;
                outCallback(u);
            });
        return Tour(std::move(tin), std::move(tout));
    }
};

}; // namespace mo

#endif
