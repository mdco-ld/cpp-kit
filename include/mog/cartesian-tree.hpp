#ifndef _MOG_CARTESIAN_TREE_HPP_
#define _MOG_CARTESIAN_TREE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/cartesian-tree.hpp>

namespace mog {

template <class T>
std::vector<int> cartesianTreeOf(const std::vector<T> &v,
								 auto compare) {
	return internal::cartesianTreeOf(v, compare);
}

template <class T>
std::vector<int> cartesianTreeOf(const std::vector<T> &v) {
	return internal::cartesianTreeOf(v, std::less<T>{});
}

}; // namespace mog

#endif
