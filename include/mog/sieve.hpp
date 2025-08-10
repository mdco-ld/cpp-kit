#ifndef _MO_SIEVE_HPP_
#define _MO_SIEVE_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/linear-sieve.hpp>
#include <mo/internal/enumerate-primes.hpp>

namespace mo {

using Sieve = internal::sieve::LinearSieve;

static const auto getPrimes = internal::sieve::enumeratePrimes;

};

#endif
