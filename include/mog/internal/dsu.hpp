#ifndef _MOG_INTERNAL_DSU_HPP_
#define _MOG_INTERNAL_DSU_HPP_

#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

namespace mog::internal {

struct DSU {
	std::vector<int> parent;
	std::vector<int> size;

	DSU(int n) : parent(n), size(n, 1) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int root(int x) {
		if (parent[x] == x) {
			return x;
		}
		return parent[x] = root(parent[x]);
	}

	bool merge(int x, int y) {
		assert(0 <= x && x < std::ssize(parent));
		assert(0 <= y && y < std::ssize(parent));
		x = root(x);
		y = root(y);
		if (x == y) {
			return false;
		}
		if (size[x] < size[y]) {
			std::swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		return true;
	}

	bool same(int x, int y) {
		assert(0 <= x && x < std::ssize(parent));
		assert(0 <= y && y < std::ssize(parent));
		return root(x) == root(y);
	}
};

class DSURollback {
	std::vector<int> parent;
	std::vector<int> rank;

	struct MergeOperation {
		int y;
		int py;
		int x;
		int rx;
	};

	std::vector<MergeOperation> operations;

  public:
	DSURollback(int n) : parent(n), rank(n, 0) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int root(int x) {
		while (x != parent[x]) {
			x = parent[x];
		}
		return x;
	}

	bool merge(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) {
			return false;
		}
		if (rank[x] < rank[y]) {
			std::swap(x, y);
		}
		operations.emplace_back(y, parent[y], x, rank[x]);
		parent[y] = x;
		if (rank[x] == rank[y]) {
			rank[x]++;
		}
		return true;
	}

	bool same(int x, int y) {
		return root(x) == root(y);
	}

	void rollback() {
		if (operations.empty()) {
			return;
		}
		auto [y, py, x, rx] = operations.back();
		operations.pop_back();
		parent[y] = py;
		rank[x] = rx;
	}
};

}; // namespace mog::internal

#endif
