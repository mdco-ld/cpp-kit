#ifndef _MO_INTERNAL_CONCEPTS_RING_HPP_
#define _MO_INTERNAL_CONCEPTS_RING_HPP_

#include <mo/internal/concepts/semiring.hpp>

namespace mo::internal::traits {

template <class S>
concept Ring = Semiring<S> && requires(S a, S b) {
	{ a - b } -> std::same_as<S>;
	{ a -= b } -> std::same_as<S &>;
	{ -a } -> std::same_as<S>;
};

}; // namespace mo::internal::traits

#endif
