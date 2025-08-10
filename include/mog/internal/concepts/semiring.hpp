#ifndef _MO_INTERNAL_CONCEPTS_SEMIRING_HPP_
#define _MO_INTERNAL_CONCEPTS_SEMIRING_HPP_

#include <concepts>
namespace mo::internal::traits {

template <class S>
concept Semiring = requires(S a, S b) {
	{ a + b } -> std::same_as<S>;
	{ a * b } -> std::same_as<S>;
	{ a += b } -> std::same_as<S &>;
	{ a *= b } -> std::same_as<S &>;
	{ S{} } -> std::same_as<S>;
	{ S{1} } -> std::same_as<S>;
};

}; // namespace mo::internal::traits

#endif
