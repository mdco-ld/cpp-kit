#ifndef _MOG_INTERNAL_CONCEPTS_HPP_
#define _MOG_INTERNAL_CONCEPTS_HPP_

#include <concepts>

namespace mog::internal::traits {

/**
 * Group concept on the operator+
 * Also requires S{} to be the neutral element
 */
template <class S>
concept Group = requires(S a, S b) {
	{ S{} };
	{ a + b } -> std::same_as<S>;
	{ a - b } -> std::same_as<S>;
	{ -a } -> std::same_as<S>;
	{ a += b } -> std::same_as<S &>;
	{ a -= b } -> std::same_as<S &>;
};

}; // namespace mog::internal::traits

#endif
