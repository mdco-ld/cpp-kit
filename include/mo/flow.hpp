#ifndef _MO_FLOW_HPP_
#define _MO_FLOW_HPP_

#include <functional>
#include <limits>
#include <queue>
#include <vector>

namespace mo {

template <typename F> class FlowGraph {
  public:
    FlowGraph(int N) : n(N), ptr(N), level(N), edges(N) {}
    void addEdge(int v, int u, F capacity) {
        edges[v].emplace_back(u, edges[u].size(), F{0}, capacity);
        edges[u].emplace_back(v, edges[v].size() - 1, F{0}, F{0});
    }
    F flow(int s, int t) {
        auto bfs = [&]() -> bool {
            std::fill(level.begin(), level.end(), -1);
            std::queue<int> q;
            level[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto &e : edges[v]) {
                    if (level[e.to] != -1 || e.flow == e.capacity) {
                        continue;
                    }
                    level[e.to] = level[v] + 1;
                    if (e.to == t) {
                        return true;
                    }
                    q.push(e.to);
                }
            }
            return false;
        };
        std::function<F(int, F)> dfs = [&](int v, F pushed) -> F {
            if (v == t) {
                return pushed;
            }
			for (; ptr[v] < edges[v].size(); ptr[v]++) {
				auto &e = edges[v][ptr[v]];
				if (level[e.to] != level[v] + 1 || e.flow == e.capacity) {
					continue;
				}
				if (F df = dfs(e.to, std::min(pushed, e.capacity - e.flow))) {
					e.flow += df;
					edges[e.to][e.rev].flow -= df;
					return df;
				}
			}
			return F{0};
        };
        F flow = F{0};
        while (bfs()) {
            static constexpr F INF = std::numeric_limits<F>::max();
            std::fill(ptr.begin(), ptr.end(), 0);
            while (F df = dfs(s, INF)) {
                flow += df;
            }
        }
        return flow;
    }

  private:
    struct Edge {
        int to;
        int rev;
        F flow;
        F capacity;
    };
    std::vector<std::vector<Edge>> edges;
    std::vector<int> ptr;
    std::vector<int> level;
    int n;
};

}; // namespace mo

#endif
