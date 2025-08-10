#ifndef _MOG_INTERNAL_PERMUTATIONS_HPP_
#define _MOG_INTERNAL_PERMUTATIONS_HPP_

#include <algorithm>
#include <numeric>
#include <vector>

namespace mog::internal {

template <class T> std::vector<int> orderOf(const std::vector<T> &v) {
	int n = v.size();
	std::vector<int> idx(n);
	std::iota(idx.begin(), idx.end(), 0);
	std::stable_sort(idx.begin(), idx.end(),
					 [&](int i, int j) { return v[i] < v[j]; });
	return idx;
}

static std::vector<int> reversePermutation(std::vector<int> &perm) {
	int n = perm.size();
	std::vector<int> out(n);
	for (int i = 0; i < n; i++) {
		out[perm[i]] = i;
	}
	return out;
}

}; // namespace mog::internal

#endif
