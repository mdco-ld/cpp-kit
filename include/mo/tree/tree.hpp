#ifndef _MO_TREE_HPP_
#define _MO_TREE_HPP_

#include <cstdint>
#include <vector>

namespace mo {

namespace tree {

template <typename T = int, bool oneBased = true> class Tree {
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
    const std::vector<T> &operator[](T v) const { return edges[v]; }

    inline int64_t size() const { return n; }
};

}; // namespace tree

}; // namespace mo

#endif
