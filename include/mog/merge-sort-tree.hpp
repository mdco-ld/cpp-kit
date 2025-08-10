#ifndef _MOG_MERGE_SORT_TREE_HPP_
#define _MOG_MERGE_SORT_TREE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/merge-sort-tree.hpp>

namespace mog {

template <class T> using MergeSortTree = internal::MergeSortTree<T>;

};

#endif
