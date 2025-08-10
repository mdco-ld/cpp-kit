#ifndef _MO_MODINT_HPP_
#define _MO_MODINT_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/modint.hpp>

namespace mo {

template<int mod>
using ModInt = internal::ModInt<mod>;

using Int1e9p7 = ModInt<1000000007>;

using Int998244353 = ModInt<998244353>;

using Int2 = ModInt<2>;

};

#endif
