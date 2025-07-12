#ifndef _MO_INTERNAL_TWO_SAT_HPP_
#define _MO_INTERNAL_TWO_SAT_HPP_

#include <mo/internal/graph/graph.hpp>
#include <mo/internal/graph/scc.hpp>
#include <mo/internal/graph/top-sort.hpp>
#include <mo/internal/permutations.hpp>

#include <vector>

namespace mo::internal {

class TwoSat {
  public:
    TwoSat(int N) : n(N), implicationGraph(2 * N), value(N) {
	}

	void addClause(int x, bool vx, int y, bool vy) { 
		implicationGraph.addEdge(x + !vx * n, y + vy * n);
		implicationGraph.addEdge(y + !vy * n, x + vx * n);
	}

	bool solve() {
		auto [g, group] = graph::scc(implicationGraph);
		for (int i = 0; i < n; i++) {
			if (group[i] == group[i + n]) {
				return false;
			}
		}
		auto order = graph::topSort(g);
		auto idx = reversePermutation(order);
		for (int i = 0; i < n; i++) {
			value[i] = idx[group[i]] > idx[group[i + n]];
		}
		return true;
	}

	const std::vector<bool> &solution() {
		return value;
	}

  private:
    int n;
    graph::DiGraph implicationGraph;
	std::vector<bool> value;
};

}; // namespace mo::internal

#endif
