#ifndef _MO_FENWICK_TREE_HPP_
#define _MO_FENWICK_TREE_HPP_

#include <mo/internal/fenwick-tree.hpp>

template<mo::internal::traits::Monoid S>
using FenwickTree = mo::internal::FenwickTree<S>;

#endif
