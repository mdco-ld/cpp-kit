#ifndef _MOG_SEGMENT_STACK_HPP_
#define _MOG_SEGMENT_STACK_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/segment-stack.hpp>

namespace mog {

template<internal::traits::Monoid S>
using SegStack = internal::SegmentStack<S>;

};

#endif
