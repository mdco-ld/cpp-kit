#ifndef _MOG_INTERNAL_GRAPH_TOP_SORT_HPP_
#define _MOG_INTERNAL_GRAPH_TOP_SORT_HPP_

#include <mog/internal/graph/graph.hpp>
#include <queue>
#include <vector>

namespace mog::internal::graph {

static void topSortDFS(const std::vector<std::vector<int>> &adj,
					   std::vector<int> &order, std::vector<bool> &visited,
					   int x) {
	if (visited[x]) {
		return;
	}
	visited[x] = true;
	for (int y : adj[x]) {
		topSortDFS(adj, order, visited, y);
	}
	order.push_back(x);
}

static std::vector<int> topSort(DiGraph &g) {
	int n = g.size();
	std::vector<int> order;
	std::vector<bool> visited(n);
	for (int i = 0; i < n; i++) {
		topSortDFS(g.getAdjacencyList(), order, visited, i);
	}
	return order;
}

static std::vector<int> maximalTopSort(DiGraph &g,
									   auto less = std::less<int>{}) {
	int n = g.size();
	auto rev = g.reverse();
	std::vector<int> deg(n);
	for (int i = 0; i < n; i++) {
		deg[i] = std::ssize(g[i]);
	}
	std::priority_queue<int, std::vector<int>, decltype(less)> q;
	for (int i = 0; i < n; i++) {
		if (deg[i] == 0) {
			q.push(i);
		}
	}
	std::vector<int> order;
	while (q.size()) {
		int current = q.top();
		q.pop();
		order.push_back(current);
		for (int j : rev[current]) {
			deg[j]--;
			if (deg[j] == 0) {
				q.push(j);
			}
		}
	}
}

}; // namespace mog::internal::graph

#endif
