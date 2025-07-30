#ifndef _MO_INTERNAL_MERGE_SORT_TREE_HPP_
#define _MO_INTERNAL_MERGE_SORT_TREE_HPP_

#include <vector>
#include <algorithm>

namespace mo::internal {

template <class T> class MergeSortTree {
  public:
	MergeSortTree() {
	}
	void build(std::vector<T> &v) {
		clear();
		n = std::ssize(v);
		t.resize(2 * n);
		for (int i = 0; i < n; i++) {
			t[i + n].push_back(v[i]);
		}
		for (int i = n - 1; i > 0; i--) {
			t[i].resize(ssize(t[i << 1]) + ssize(t[i << 1 | 1]));
			std::merge(t[i << 1].begin(), t[i << 1].end(), t[i << 1 | 1].begin(), t[i << 1 | 1].end(), t[i].begin());
		}
	}
	int countLess(int l, int r, T x) {
		return countPred(l, r, x, [](auto begin, auto end, T x) { return std::lower_bound(begin, end, x) - begin; });
	}
	int countLessEq(int l, int r, T x) {
		return countPred(l, r, x, [](auto begin, auto end, T x) { return std::upper_bound(begin, end, x) - begin; });
	}
	int countGreater(int l, int r, T x) {
		return countPred(l, r, x, [](auto begin, auto end, T x) { return end - std::upper_bound(begin, end, x); });
	}
	int countGreaterEq(int l, int r, T x) {
		return countPred(l, r, x, [](auto begin, auto end, T x) { return end - std::lower_bound(begin, end, x); });
	}
	void clear() {
		t.clear();
	}
  private:
	int n;
	std::vector<std::vector<T>> t;
	int countPred(int l, int r, T x, auto pred) {
		int cnt = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				cnt += pred(t[l].begin(), t[l].end(), x);
				l++;
			}
			if (r & 1) {
				r--;
				cnt += pred(t[r].begin(), t[r].end(), x);
			}
		}
		return cnt;
	}
};

}; // namespace mo::internal

#endif
