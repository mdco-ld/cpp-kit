#ifndef _MOG_HASH_HPP_
#define _MOG_HASH_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/hash.hpp>

namespace mog {

template <unsigned int N = 0> using hash1 = internal::Hash<20040419, N>;

template <unsigned int N = 0>
using hash2 = internal::Hash2<20040419, 0x6d696775656cull, N>;

template <unsigned int N = 0>
using hash3 =
	internal::Hash3<20040419, 0x6d696775656cull, 0x6d6f6e6f6963ull, N>;

template <unsigned int N = 0>
using hashs = internal::OrderedHash<20040419, 0x6d696775656cull, N>;

}; // namespace mog

#endif
