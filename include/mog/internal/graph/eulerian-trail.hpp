#ifndef _MOG_INTERNAL_EULERIAN_TRAIL_HPP_
#define _MOG_INTERNAL_EULERIAN_TRAIL_HPP_

#include <vector>
#include <mog/internal/graph/graph.hpp>

namespace mog::internal::graph {

static std::pair<std::vector<int>, std::vector<int>> directedEulerianTrail(std::vector<std::pair<int, int>> &edges) {
	std::vector<int> trail;
	std::vector<int> trailEdges;
	return {trail, trailEdges};
}

static std::vector<int> eulerianTrail(DiGraph &g) {
	std::vector<int> trail;
	std::vector<int> stack;
	int n = g.size();
	std::vector<int> nx(n);
	int edgeCnt = 0;
	for (int i = 0; i < n; i++) {
		edgeCnt += g[i].size();
	}
	stack.push_back(0);
	while (stack.size()) {
		int cur = stack.back();
		if (nx[cur] == g[cur].size()) {
			stack.pop_back();
			trail.push_back(cur);
		} else {
			stack.push_back(g[cur][nx[cur]]);
			nx[cur]++;
		}
	}
	if (std::ssize(trail) < edgeCnt + 1) {
		return {};
	}
	return trail;
}

};

#endif
