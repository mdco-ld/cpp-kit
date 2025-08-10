#ifndef _MOG_FENWICK_TREE_HPP_
#define _MOG_FENWICK_TREE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/fenwick-tree.hpp>

namespace mog {

template <mog::internal::traits::Monoid S>
using FenwickTree = mog::internal::FenwickTree<S>;

};

#endif
