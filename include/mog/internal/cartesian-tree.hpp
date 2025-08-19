#ifndef _MOG_INTERNAL_CARTESIAN_TREE_HPP_
#define _MOG_INTERNAL_CARTESIAN_TREE_HPP_

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

namespace mog::internal {

template <class T>
std::vector<int> cartesianTreeOf(const std::vector<T> &v, auto compare) {
	int n = std::ssize(v);
	std::vector<int> par(n);
	std::vector<int> idx(n);
	std::iota(idx.begin(), idx.end(), 0);
	std::stable_sort(idx.begin(), idx.end(), [&v, &compare](int i, int j) {
		return compare(v[i], v[j]);
	});
	std::fill(par.begin(), par.end(), idx[0]);
	std::set<int> st;
	for (int i : idx) {
		auto right = st.upper_bound(i);
		if (right != st.end()) {
			par[i] = *right;
		}
		if (right != st.begin()) {
			auto left = std::prev(right);
			if (!compare(v[*left], v[par[i]])) {
				par[i] = *left;
			}
		}
		st.insert(i);
	}
	return par;
}

}; // namespace mog::internal

#endif
