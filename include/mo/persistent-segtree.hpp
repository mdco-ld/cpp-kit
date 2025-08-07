#ifndef _MO_PERSISTENT_SEGTREE_HPP_
#define _MO_PERSISTENT_SEGTREE_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/persistent-segment-tree.hpp>
#include <mo/internal/utils.hpp>

namespace mo {

template<internal::traits::Monoid S>
using PST = internal::PersistentSegmentTree<S>;

template<class T>
using MaxPST = internal::PersistentSegmentTree<internal::utils::traits::MaxMonoid<T>>;

template<class T>
using MinPST = internal::PersistentSegmentTree<internal::utils::traits::MinMonoid<T>>;

};

#endif
