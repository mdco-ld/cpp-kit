#ifndef _MOG_MODINT_HPP_
#define _MOG_MODINT_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/modint.hpp>

namespace mog {

template <int mod> using ModInt = internal::ModInt<mod>;

using Int1e9p7 = ModInt<1000000007>;

using Int998244353 = ModInt<998244353>;

using Int2 = ModInt<2>;

}; // namespace mog

#endif
