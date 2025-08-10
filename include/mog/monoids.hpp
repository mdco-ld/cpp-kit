#ifndef _MO_MONOIDS_HPP_
#define _MO_MONOIDS_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/utils.hpp>

namespace mo {

template <class T> using MaxMonoid = internal::utils::traits::MaxMonoid<T>;

template <class T> using MinMonoid = internal::utils::traits::MinMonoid<T>;

template <class T> using GcdMonoid = internal::utils::traits::GcdMonoid<T>;

template <class T> using LcmMonoid = internal::utils::traits::LcmMonoid<T>;

template <class T>
using ProductMonoid = internal::utils::traits::ProductMonoid<T>;

template <class T>
using AffineMonoid = internal::utils::traits::AffineMonoid<T>;

template <class T, T (*sum)(T, T), T (*zero)()>
using MonoidOf = internal::utils::traits::MonoidOf<T, sum, zero>;

template<internal::traits::Monoid S>
using ReverseMonoid = internal::utils::traits::ReverseMonoid<S>;

}; // namespace mo

#endif
