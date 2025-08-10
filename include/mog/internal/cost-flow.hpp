#ifndef _MOG_INTERNAL_COST_FLOW_HPP_
#define _MOG_INTERNAL_COST_FLOW_HPP_

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

namespace mog::internal {

template <class Cap, class Cost> class CostFlowGraph {
  public:
	struct Edge {
		int from;
		int to;
		Cap cap;
		Cost cost;
	};

	CostFlowGraph(int N) : n(N) {}

	void addEdge(int from, int to, Cap cap, Cost cost) {
		edges.emplace_back(from, to, cap, cost);
		edges.emplace_back(to, from, 0, -cost);
	}

	std::pair<Cap, Cost> minCostFlow(int s, int t) {
		return minCostFlow(s, t, std::numeric_limits<Cap>::max());
	}

	std::pair<Cap, Cost> minCostFlow(int s, int t, Cap flowCap) {
		Cap f = 0;
		Cost c = 0;
		std::vector<Cost> dist(n);
		std::vector<int> par(n);
		while (f < flowCap) {
			std::fill(dist.begin(), dist.end(),
					  std::numeric_limits<Cost>::max());
			std::fill(par.begin(), par.end(), -1);
			dist[s] = 0;
			for (int iter = 1; iter < n; iter++) {
				int i = 0;
				for (auto [a, b, cap, cost] : edges) {
					if (cap == 0) {
						i++;
						continue;
					}
					if (par[b] == -1 || dist[a] + cost < dist[b]) {
						par[b] = i;
						dist[b] = dist[a] + cost;
					}
					i++;
				}
			}
			if (par[t] == -1) {
				break;
			}
			Cap df = flowCap - f;
			for (int i = t; i != s; i = edges[par[i]].a) {
				df = min(df, edges[par[i]].cap);
			}
			f += df;
			for (int i = t; i != s; i = edges[par[i]].a) {
				auto &e = edges[par[i]];
				auto &rev = edges[par[i] ^ 1];
				e.cap -= df;
				c += e.cost * df;
				rev.cap += df;
			}
		}
		return {f, c};
	}

  private:
	std::vector<Edge> edges;
	int n;
};

}; // namespace mog::internal

#endif
