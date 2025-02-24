#ifndef _MO_GRAPH_HPP_
#define _MO_GRAPH_HPP_

#include <vector>

namespace mo {

class Graph {
  private:
    std::vector<std::vector<int>> edges;

  public:
    Graph() {}

    void addEdge(int u, int v) {
        if (std::max(u, v) >= edges.size()) {
            edges.resize(std::max(u, v) + 1);
        }
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

	void clear() {
		edges.clear();
	}

	std::vector<int> &operator[](int u) {
		return edges[u];
	}
};

}; // namespace mo

#endif
