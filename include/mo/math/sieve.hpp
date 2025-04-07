#ifndef _MO_MATH_SIEVE_HPP_
#define _MO_MATH_SIEVE_HPP_

#include <vector>

namespace mo {

namespace math {

constexpr std::vector<int> getPrimes(int n) {
    std::vector<int> primes;
    std::vector<int> lowestPrime(n + 1);
    for (int i = 2; i <= n; i++) {
        if (lowestPrime[i] == 0) {
            lowestPrime[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; i * primes[j] <= n; j++) {
            lowestPrime[i * primes[j]] = primes[j];
            if (primes[j] == lowestPrime[i]) {
                break;
            }
        }
    }
    return primes;
}

class Sieve {
  public:
    constexpr Sieve(int n) : lowestPrime(n + 1), squarefree(n + 1) {
        for (int i = 2; i <= n; i++) {
            if (lowestPrime[i] == 0) {
                lowestPrime[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; i * primes[j] <= n; j++) {
                lowestPrime[i * primes[j]] = primes[j];
                if (primes[j] == lowestPrime[i]) {
                    break;
                }
            }
        }
        squarefree[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (lowestPrime[i] == lowestPrime[i / lowestPrime[i]]) {
                squarefree[i] = squarefree[i / lowestPrime[i]];
            } else {
                squarefree[i] = lowestPrime[i] * squarefree[i / lowestPrime[i]];
            }
        }
    }

    constexpr inline int operator[](int i) { return primes[i]; }

    constexpr inline int getLowestPrime(int n) { return lowestPrime[n]; }

    constexpr inline int getSquarefree(int n) { return squarefree[n]; }

  private:
    std::vector<int> primes;
    std::vector<int> lowestPrime;
    std::vector<int> squarefree;
};

}; // namespace math

}; // namespace mo

#endif
