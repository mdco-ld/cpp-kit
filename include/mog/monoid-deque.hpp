#ifndef _MOG_MONOID_DEQUE_
#define _MOG_MONOID_DEQUE_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/monoid-deque.hpp>

namespace mog {

template <internal::traits::Monoid S>
using MonoidDeque = internal::MonoidDeque<S>;

};

#endif
