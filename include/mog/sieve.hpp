#ifndef _MOG_SIEVE_HPP_
#define _MOG_SIEVE_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/enumerate-primes.hpp>
#include <mog/internal/linear-sieve.hpp>

namespace mog {

using Sieve = internal::sieve::LinearSieve;

static const auto getPrimes = internal::sieve::enumeratePrimes;

}; // namespace mog

#endif
