#ifndef _MOG_MONOID_QUEUE_
#define _MOG_MONOID_QUEUE_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/monoid-queue.hpp>

namespace mog {

template <internal::traits::Monoid S>
using MonoidQueue = internal::RightMonoidStack<S>;

};

#endif
