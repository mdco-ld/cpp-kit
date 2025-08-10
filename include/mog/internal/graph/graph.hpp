#ifndef _MOG_INTERNAL_GRAPH_HPP_
#define _MOG_INTERNAL_GRAPH_HPP_

#include <concepts>
#include <utility>
#include <variant>
#include <vector>

namespace mog::internal::graph {

class Graph {
  public:
	Graph(int N) : n(N), adj(N) {}

	void addEdge(int x, int y) {
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	inline int size() { return n; }

	std::vector<int> &operator[](int i) { return adj[i]; }

	const std::vector<std::vector<int>> &getAdjacencyList() { return adj; }

  private:
	int n;
	std::vector<std::vector<int>> adj;
};

class DiGraph {
  public:
	DiGraph(int N) : n(N), adj(N) {}

	void addEdge(int x, int y) { adj[x].push_back(y); }

	inline int size() { return n; }

	std::vector<int> &operator[](int i) { return adj[i]; }

	const std::vector<std::vector<int>> &getAdjacencyList() { return adj; }

	DiGraph reverse() const {
		DiGraph result(n);
		for (int i = 0; i < n; i++) {
			for (int j : adj[i]) {
				result.addEdge(j, i);
			}
		}
		return result;
	}

  private:
	int n;
	std::vector<std::vector<int>> adj;
};

template <class Weight> class WGraph {
  public:
	const static std::monostate _isWGraphTag;

	WGraph(int N) : n(N), adj(N) {}

	void addEdge(int x, int y, Weight w) {
		adj[x].emplace_back(w, y);
		adj[y].emplace_back(w, x);
	}

	inline int size() { return n; }

	std::vector<std::pair<Weight, int>> &operator[](int i) { return adj[i]; }

  private:
	int n;
	std::vector<std::vector<std::pair<Weight, int>>> adj;
};

template <class Weight> class WDiGraph {
  public:
	const static std::monostate _isWGraphTag;

	WDiGraph(int N) : n(N), adj(N) {}

	void addEdge(int x, int y, Weight w) { adj[x].emplace_back(w, y); }

	inline int size() { return n; }

	std::vector<std::pair<Weight, int>> &operator[](int i) { return adj[i]; }

  private:
	int n;
	std::vector<std::vector<std::pair<Weight, int>>> adj;
};

template <class T>
concept GraphType = std::same_as<T, Graph> || std::same_as<T, DiGraph>;

template <class T>
concept WGraphType = requires { T::_isWGraphTag; };

}; // namespace mog::internal::graph

#endif
