<div align="center">

# 🚀 cpp-kit

**A Modern C++ Competitive Programming Library**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C%2B%2B-20-00599C.svg?logo=c%2B%2B)](https://isocpp.org/)

*Fast, reliable, and easy-to-use data structures and algorithms for competitive programming*

</div>

---

## 📚 About

**cpp-kit** is a comprehensive collection of data structures and algorithms optimized for competitive programming. It provides header-only C++ implementations that are easy to integrate into your solutions, with a utility script to combine everything into a single file for online judges.

## ✨ Features

- 🎯 **Header-only library** - No compilation required, just include and go
- 📦 **Single-file expansion** - Combine all includes into one file for submission
- ⚡ **Optimized implementations** - Fast and memory-efficient
- 🔧 **Easy to use** - Simple, intuitive API design
- 🧪 **Battle-tested** - Used in real competitive programming contests

## 📥 Installation

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 10+)
- Python 3 (for the expand script)

### Setup on Linux

1. **Clone the repository**
   ```bash
   git clone https://github.com/mdco-ld/cpp-kit.git
   cd cpp-kit
   ```

2. **Run the setup script**
   ```bash
   chmod +x setup.sh
   ./setup.sh
   ```
   
   This will:
   - ✅ Add the library path to your environment variables
   - ✅ Create a symbolic link to `expand.py` in `~/bin/` (if it exists)

3. **Reload your shell configuration**
   ```bash
   source ~/.bashrc  # or source ~/.zshrc for zsh users
   ```

## 🎯 Quick Start

### Basic Usage

Include the header for the data structure or algorithm you need:

```cpp
#include <vector>
#include <mog/fenwick-tree.hpp>

// Example: Count inversions in a permutation
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

### Expanding to Single File

For online judges that don't support custom includes, use the `expand.py` script to merge all library includes into a single file:

```bash
expand.py your_solution.cpp
```

This creates `sol.cpp` with all library code inlined, ready for submission! 🎉

## 📦 Available Data Structures & Algorithms

### Data Structures
- **Trees**
  - `fenwick-tree.hpp` - Binary Indexed Tree (Fenwick Tree)
  - `segtree.hpp` - Segment Tree with lazy propagation support
  - `persistent-segtree.hpp` - Persistent Segment Tree
  - `merge-sort-tree.hpp` - Merge Sort Tree
  - `cartesian-tree.hpp` - Cartesian Tree
  
- **Disjoint Sets & Unions**
  - `dsu.hpp` - Disjoint Set Union (Union-Find)
  
- **Queues & Stacks**
  - `monoid-stack.hpp` - Stack with monoid operations
  - `monoid-queue.hpp` - Queue with monoid operations
  - `monoid-deque.hpp` - Deque with monoid operations
  - `segment-stack.hpp` - Segment Stack

- **Specialized Structures**
  - `sparse-array.hpp` - Sparse Array
  - `range-map.hpp` - Range Map
  - `suffix-max.hpp` - Suffix Maximum

### Algorithms

- **Graph Algorithms** (`graph/`)
  - Graph representation and traversal
  - BFS, DFS
  - Topological Sort
  - Strongly Connected Components (SCC)
  - Eulerian Trail
  - Tree algorithms

- **String Algorithms** (`strings/`)
  - `kmp.hpp` - Knuth-Morris-Pratt pattern matching

- **Mathematics** (`math/`)
  - `modint.hpp` - Modular arithmetic
  - `matrix.hpp` - Matrix operations
  - `computations.hpp` - Common mathematical computations
  - `number-theory.hpp` - Number theoretic functions
  - `sieve.hpp` - Prime number sieve

- **Flow & Matching**
  - `cost-flow.hpp` - Minimum Cost Flow
  - `two-sat.hpp` - 2-SAT solver

- **Utilities**
  - `hash.hpp` - Custom hash functions
  - `array.hpp` - Array utilities
  - `bs.hpp` - Binary search utilities
  - `monoids.hpp` - Common monoid definitions
  - `debug.hpp` - Debug utilities (ignored during expansion)

## 🛠️ Template

The repository includes a `template.cpp` file with common competitive programming setup:
- Fast I/O configuration
- Common aliases and macros
- Random number generator setup
- Conditional debug macro integration

## 🤝 Contributing

Contributions are welcome! Feel free to:
- 🐛 Report bugs
- 💡 Suggest new features or data structures
- 🔧 Submit pull requests with improvements

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Miguel Oliveira**

---

<div align="center">

⭐ **Star this repository if you find it helpful!** ⭐

Made with ❤️ for the competitive programming community

</div>
