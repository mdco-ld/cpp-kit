#ifndef _MO_FENWICK_TREE_HPP_
#define _MO_FENWICK_TREE_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/fenwick-tree.hpp>

namespace mo {

template<mo::internal::traits::Monoid S>
using FenwickTree = mo::internal::FenwickTree<S>;

};

#endif
