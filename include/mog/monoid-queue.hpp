#ifndef _MO_MONOID_QUEUE_
#define _MO_MONOID_QUEUE_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/monoid-queue.hpp>

namespace mo {

template<internal::traits::Monoid S>
using MonoidQueue = internal::RightMonoidStack<S>;

};

#endif
