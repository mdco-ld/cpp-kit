#ifndef _MOG_INTERNAL_CONCEPTS_MONOID_HPP_
#define _MOG_INTERNAL_CONCEPTS_MONOID_HPP_

#include <concepts>

namespace mog::internal::traits {

/**
 * Monoid concept on the operator+
 * Also requires S{} to be the neutral element
 */
template <class S>
concept Monoid = requires(S a, S b) {
	{ S{} };
	{ a + b } -> std::same_as<S>;
	{ a += b } -> std::same_as<S &>;
};

}; // namespace mog::internal::traits

#endif
