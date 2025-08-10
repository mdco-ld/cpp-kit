#ifndef _MO_MONOID_STACK_
#define _MO_MONOID_STACK_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/monoid-stack.hpp>

namespace mo {

template<internal::traits::Monoid S>
using LeftMonoidStack = internal::RightMonoidStack<S>;

template<internal::traits::Monoid S>
using RightMonoidStack = internal::RightMonoidStack<S>;

};

#endif
