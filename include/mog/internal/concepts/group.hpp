#ifndef _MO_INTERNAL_CONCEPTS_HPP_
#define _MO_INTERNAL_CONCEPTS_HPP_

#include <concepts>

namespace mo::internal::traits {

/**
 * Group concept on the operator+
 * Also requires S{} to be the neutral element
 */
template<class S>
concept Group = requires (S a, S b) {
	{ S{} };
	{ a + b } -> std::same_as<S>;
	{ a - b } -> std::same_as<S>;
	{ -a } -> std::same_as<S>;
	{ a += b } -> std::same_as<S &>;
	{ a -= b } -> std::same_as<S &>;
};

};

#endif
