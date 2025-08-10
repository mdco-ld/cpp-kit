#ifndef _MOG_INTERNAL_CONCEPTS_RING_HPP_
#define _MOG_INTERNAL_CONCEPTS_RING_HPP_

#include <mog/internal/concepts/semiring.hpp>

namespace mog::internal::traits {

template <class S>
concept Ring = Semiring<S> && requires(S a, S b) {
	{ a - b } -> std::same_as<S>;
	{ a -= b } -> std::same_as<S &>;
	{ -a } -> std::same_as<S>;
};

}; // namespace mog::internal::traits

#endif
