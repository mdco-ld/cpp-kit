#ifndef _MO_SEGTREE_HPP_
#define _MO_SEGTREE_HPP_

#include <mo/internal/segment-tree.hpp>
#include <mo/internal/utils.hpp>

namespace mo {

template<mo::internal::traits::Monoid S>
using Segtree = mo::internal::SegmentTree<S>;

template<class T>
using MinSegtree = Segtree<mo::internal::utils::traits::MinMonoid<T>>;

template<class T>
using MaxSegtree = Segtree<mo::internal::utils::traits::MaxMonoid<T>>;

};

#endif
