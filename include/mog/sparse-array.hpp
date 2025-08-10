#ifndef _MOG_SPARSE_ARRAY_HPP_
#define _MOG_SPARSE_ARRAY_HPP_

#include <algorithm>
#include <array>
#include <mog/internal/concepts/monoid.hpp>
#include <vector>

namespace mog {

template <internal::traits::Monoid S> class MonoidSparseArray {
	using Index = unsigned long long;

  public:
	MonoidSparseArray() { trie.emplace_back(); }

	S operator[](Index i) {
		int p = 0;
		for (int h = 63; h >= 0; h--) {
			int to = i >> h & 1;
			if (!trie[p].child[to]) {
				return S{};
			}
			p = trie[p].child[to];
		}
		return trie[p].value;
	}

	void set(Index i, S value) {
		int p = 0;
		std::array<int, 64> points;
		for (int h = 63; h >= 0; h--) {
			points[h] = p;
			int to = i >> h & 1;
			if (!trie[p].child[to]) {
				trie[p].child[to] = trie.size();
				trie.emplace_back();
			}
			p = trie[p].child[to];
		}
		trie[p].value = value;
		for (int i : points) {
			trie[i].value =
				getValue(trie[i].child[0]) + getValue(trie[i].child[1]);
		}
	}

  private:
	struct Node {
		std::array<int, 2> child;
		S value;
		Node() : value(S{}) { std::fill(child.begin(), child.end(), 0); }
	};

	inline S getValue(int node) {
		if (!node) {
			return S{};
		}
		return trie[node].value;
	}

	std::vector<Node> trie;
};

}; // namespace mog

#endif
