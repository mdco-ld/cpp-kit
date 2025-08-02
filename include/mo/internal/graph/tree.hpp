#ifndef _MO_INTERNAL_GRAPH_TREE_HPP_
#define _MO_INTERNAL_GRAPH_TREE_HPP_

#include <vector>
namespace mo::internal {

class Tree {
public:
	Tree(int N): adj(N), n(N) {
	}
	void addEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	std::vector<int> &operator[](int i) {
		return adj[i];
	}
	int size() {
		return n;
	}
private:
	std::vector<std::vector<int>> adj;
	int n;
};

};

#endif
