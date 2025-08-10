#ifndef _MOG_MONOID_STACK_
#define _MOG_MONOID_STACK_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/monoid-stack.hpp>

namespace mog {

template <internal::traits::Monoid S>
using LeftMonoidStack = internal::RightMonoidStack<S>;

template <internal::traits::Monoid S>
using RightMonoidStack = internal::RightMonoidStack<S>;

}; // namespace mog

#endif
