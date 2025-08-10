#ifndef _MOG_INTERNAL_CONCEPTS_SEMIGROUP_HPP_
#define _MOG_INTERNAL_CONCEPTS_SEMIGROUP_HPP_

#include <concepts>

namespace mog::internal::traits {

/**
 * Semigroup concept on the operator+
 */
template <class S>
concept Semigroup = requires(S a, S b) {
	{ a + b } -> std::same_as<S>;
	{ a += b } -> std::same_as<S &>;
};

}; // namespace mog::internal::traits

#endif
