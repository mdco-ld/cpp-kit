#ifndef _MO_INTERNAL_GRAPH_BFS_HPP_
#define _MO_INTERNAL_GRAPH_BFS_HPP_

#include <limits>
#include <mo/internal/graph/graph.hpp>
#include <queue>

namespace mo::internal::graph {

template <GraphType G>
static std::pair<std::vector<int>, std::vector<int>> bfs(G &g, int s) {
    int n = g.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> par(n, -1);
    std::queue<int> q;
    q.push(s);
    par[s] = s;
    dist[s] = 0;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (par[y] == -1) {
                par[y] = x;
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }
    return {dist, par};
}

template <GraphType G>
static std::pair<std::vector<int>, std::vector<int>> bfs(G &g,
                                                         std::vector<int> ss) {
    int n = g.size();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> par(n, -1);
    std::queue<int> q;
    for (int s : ss) {
        par[s] = s;
        dist[s] = 0;
        q.push(s);
    }
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int y : g[x]) {
            if (par[y] == -1) {
                dist[y] = dist[x] + 1;
                par[y] = x;
                q.push(y);
            }
        }
    }
    return {dist, par};
}

}; // namespace mo::internal::graph

#endif
