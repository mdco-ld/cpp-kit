# cpp-kit

C++ kit for competitive programming

# Setup

## On Linux

1. Clone the repository
2. Run `./setup.sh`. This does two things:
    - Add the library path environment variable to your library path.
    - Create a symbolic link to the expand.py script in the directory `~/bin/` if it exists.

# Usage

Include the header corresponding to the data structure/algorithm you want to use.

Example:
```cpp
#include <vector>
#include <mog/fenwick-tree.hpp>

// Counts inversions in a permutation of (0..n - 1)
int countInversions(const std::vector<int> &permutation) {
    int n = std::ssize(permutation);
    mog::FenwickTree<int> fenwickTree(n);
    int inversions = 0;
    for (int i = 0; i < n; i++) {
        inversions += fenwickTree.sum(permutation[i], n);
        fenwickTree.add(permutation[i], 1);
    }
    return inversions;
}
```

To compile everything into a single source file, use the script `expand.py`. Example:
```bash
expand.py inversions.cpp
```

Will create a file called `sol.cpp` without any includes for this library.

