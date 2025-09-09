#ifndef _MOG_SUFFIX_MAX_HPP_
#define _MOG_SUFFIX_MAX_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/suffix-max.hpp>

namespace mog {

template <class T, bool (*less)(T, T) = [](T x, T y) { return x < y; }>
using SuffixMax = internal::SuffixMax<T, less>;

}; // namespace mog

#endif
