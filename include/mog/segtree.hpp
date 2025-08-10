#ifndef _MOG_SEGTREE_HPP_
#define _MOG_SEGTREE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/segment-tree.hpp>
#include <mog/internal/utils.hpp>

namespace mog {

template <mog::internal::traits::Monoid S>
using Segtree = mog::internal::SegmentTree<S>;

template <class T>
using MinSegtree = Segtree<mog::internal::utils::traits::MinMonoid<T>>;

template <class T>
using MaxSegtree = Segtree<mog::internal::utils::traits::MaxMonoid<T>>;

}; // namespace mog

#endif
