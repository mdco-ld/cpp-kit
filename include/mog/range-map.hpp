#ifndef _MOG_RANGE_MAP_HPP_
#define _MOG_RANGE_MAP_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/range-map.hpp>

namespace mog {

template<class Key, class Value, Value (*id)() = []() { return Value{}; }>
using RangeMap = internal::RangeMap<Key, Value, id>;

};

#endif
