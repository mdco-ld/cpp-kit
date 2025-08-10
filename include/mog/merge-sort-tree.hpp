#ifndef _MO_MERGE_SORT_TREE_HPP_
#define _MO_MERGE_SORT_TREE_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/merge-sort-tree.hpp>

namespace mo {

template<class T>
using MergeSortTree = internal::MergeSortTree<T>;

};

#endif
