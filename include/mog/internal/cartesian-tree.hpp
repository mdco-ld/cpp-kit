#ifndef _MOG_INTERNAL_CARTESIAN_TREE_HPP_
#define _MOG_INTERNAL_CARTESIAN_TREE_HPP_

#include <vector>

namespace mog::internal {

template <class T>
std::vector<int> cartesianTreeOf(const std::vector<T> &v, auto compare) {
	int n = std::ssize(v);
	std::vector<int> par(n);
	std::vector<int> stack;
	stack.push_back(0);
	for (int i = 1; i < n; i++) {
		if (compare(v[stack.back()], v[i])) {
			stack.push_back(i);
			continue;
		}
		int left = stack.back();
		stack.pop_back();
		while (stack.size() && compare(v[i], v[stack.back()])) {
			par[left] = stack.back();
			left = stack.back();
			stack.pop_back();
		}
		par[left] = i;
		stack.push_back(i);
	}
	int right = stack.back();
	stack.pop_back();
	while (stack.size()) {
		par[right] = stack.back();
		right = stack.back();
		stack.pop_back();
	}
	par[right] = right;
	return par;
}

}; // namespace mog::internal

#endif
