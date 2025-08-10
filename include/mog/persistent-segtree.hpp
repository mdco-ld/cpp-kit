#ifndef _MOG_PERSISTENT_SEGTREE_HPP_
#define _MOG_PERSISTENT_SEGTREE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/persistent-segment-tree.hpp>
#include <mog/internal/utils.hpp>

namespace mog {

template <internal::traits::Monoid S>
using PST = internal::PersistentSegmentTree<S>;

template <class T>
using MaxPST =
	internal::PersistentSegmentTree<internal::utils::traits::MaxMonoid<T>>;

template <class T>
using MinPST =
	internal::PersistentSegmentTree<internal::utils::traits::MinMonoid<T>>;

}; // namespace mog

#endif
