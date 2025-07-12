#ifndef _MO_INTERNAL_GRAPH_SCC_HPP_
#define _MO_INTERNAL_GRAPH_SCC_HPP_

#include <algorithm>
#include <mo/internal/graph/graph.hpp>
#include <mo/internal/graph/top-sort.hpp>
#include <set>
#include <utility>
#include <vector>

namespace mo::internal::graph {

static std::pair<DiGraph, std::vector<int>> scc(DiGraph &g) {
    int n = g.size();
    auto rev = g.reverse();
    auto order = topSort(g);
    std::reverse(order.begin(), order.end());
    std::vector<bool> visited(n);
    std::vector<int> component(n);
    int cnt = 0;
    for (int i : order) {
        if (!visited[i]) {
            std::queue<int> q;
            q.push(i);
            visited[i] = true;
            while (q.size()) {
                int x = q.front();
                q.pop();
                component[x] = cnt;
                for (int y : rev[x]) {
                    if (!visited[y]) {
                        q.push(y);
                        visited[y] = true;
                    }
                }
            }
            cnt++;
        }
    }
    std::set<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
            if (component[i] != component[j]) {
                edges.emplace(component[i], component[j]);
            }
        }
    }
    DiGraph result(cnt);
    for (auto [a, b] : edges) {
        result.addEdge(a, b);
    }
    return {result, component};
}

}; // namespace mo::internal::graph

#endif
