# cpp-kit

C++ library for competitive programming.

## Quick Start

1. Clone the repository
2. Run `./setup.sh` to:
   - Add library path to your shell environment
   - Link expand.py to ~/bin/ for easy access

## What's Included

### Data Structures
- **FenwickTree** - Binary indexed tree for prefix sums
- **Segtree** - Segment tree with monoid operations (includes MinSegtree, MaxSegtree)
- **PST** - Persistent segment tree (includes MinPST, MaxPST)
- **MergeSortTree** - Segment tree of sorted vectors for range queries
- **DSU** - Disjoint set union with path compression
- **MonoidQueue, MonoidStack, MonoidDeque** - Queue/stack/deque with range queries
- **RangeMap** - Map data structure for range operations
- **SparseArray** - Memory-efficient array for sparse data
- **CartesianTree** - Build cartesian trees from arrays

### Algorithms
- **TwoSat** - 2-SAT solver
- **CostFlowGraph** - Min-cost max-flow algorithm
- **Sieve** - Linear sieve for prime factorization
- **bs** - Binary search utilities
- **getPrimes** - Prime enumeration

### Math & Number Theory
- **ModInt** - Modular arithmetic (includes Int1e9p7, Int998244353)
- **Monoids** - Pre-built monoid types (MaxMonoid, MinMonoid, GcdMonoid, etc.)

### Utilities
- **hash1, hash2, hash3, hashs** - Rolling hash implementations
- **debug** - Debug printing utilities (excluded when submitting)

## Usage Examples

### Counting Inversions with Fenwick Tree
```cpp
#include <vector>
#include <mog/fenwick-tree.hpp>

int countInversions(const std::vector<int> &perm) {
    int n = std::ssize(perm);
    mog::FenwickTree<int> ft(n);
    int inversions = 0;
    for (int i = 0; i < n; i++) {
        inversions += ft.sum(perm[i], n);
        ft.add(perm[i], 1);
    }
    return inversions;
}
```

### Range Minimum Query with Segment Tree
```cpp
#include <vector>
#include <mog/segtree.hpp>

std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
mog::MinSegtree<int> seg;
seg.build(arr);

int min_val = seg.sum(2, 6).value;  // Min of arr[2..6)
seg.set(3, 10);                      // Update arr[3] = 10
```

### Modular Arithmetic
```cpp
#include <mog/modint.hpp>

using mint = mog::Int1e9p7;  // mod 10^9+7

mint factorial(int n) {
    mint result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

### 2-SAT Problem
```cpp
#include <mog/two-sat.hpp>

int n = 3;  // 3 boolean variables
mog::TwoSat sat(n);

// Add clauses: (x0 OR x1), (NOT x0 OR x2), etc.
sat.addClause(0, true, 1, true);
sat.addClause(0, false, 2, true);

if (sat.solve()) {
    auto solution = sat.solution();  // Get assignment
}
```

### Disjoint Set Union
```cpp
#include <mog/dsu.hpp>

mog::DSU dsu(n);
dsu.merge(u, v);       // Union two elements
bool connected = dsu.same(u, v);  // Check if same component
```

### Prime Sieve
```cpp
#include <mog/sieve.hpp>

mog::Sieve sieve(1000000);
auto primes = mog::getPrimes(1000000);  // All primes up to 10^6

// Check if number is prime
bool is_prime = sieve.isPrime(17);

// Get smallest prime factor
int spf = sieve.getSpf(12);  // Returns 2
```

### Binary Search
```cpp
#include <mog/bs.hpp>

int l = 0, r = 1000000;
mog::bs(l, r, [](int x) {
    return check(x);  // Find largest x where check(x) is true
});
```

## Submitting Solutions

Use `expand.py` to merge all library code into a single file for submission:

```bash
expand.py solution.cpp
```

This creates `sol.cpp` with all library includes expanded inline. The debug.hpp header is automatically excluded.

## Template

Use `template.cpp` as a starting point for new problems. It includes:
- Fast I/O setup
- Common type aliases
- Debug macros (only active locally)
- Multi-test case structure

