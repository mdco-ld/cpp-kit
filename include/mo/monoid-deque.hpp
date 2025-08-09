#ifndef _MO_MONOID_DEQUE_
#define _MO_MONOID_DEQUE_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/monoid-deque.hpp>

namespace mo {

template<internal::traits::Monoid S>
using MonoidDeque = internal::MonoidDeque<S>;

};

#endif
