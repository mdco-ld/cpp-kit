#ifndef _MO_INTERNAL_BINARY_TRIE_HPP_
#define _MO_INTERNAL_BINARY_TRIE_HPP_

#include <mo/internal/concepts/monoid.hpp>

#include <array>
#include <bitset>
#include <vector>

namespace mo::internal {

template <int size> class BinaryTrie {
    using u64 = unsigned long long;

  public:
    BinaryTrie() { nodes.emplace_back(std::array<int, 2>{-1, -1}); }

    void insert(u64 x) {
        int p = 0;
        for (int i = size - 1; i >= 0; i--) {
            int bit = !(x >> i & 1);
            if (nodes[p][bit] == -1) {
                nodes[p][bit] = nodes.size();
                nodes.emplace_back(std::array<int, 2>{-1, -1});
            }
            p = nodes[p][bit];
        }
    }

    void insert(std::bitset<size> x) {
        int p = 0;
        for (int i = size - 1; i >= 0; i--) {
            int bit = !x.test(i);
            if (nodes[p][bit] == -1) {
                nodes[p][bit] = nodes.size();
                nodes.emplace_back(std::array<int, 2>{-1, -1});
            }
            p = nodes[p][bit];
        }
    }

    u64 maxXor(u64 x) {
        int p = 0;
        u64 result = 0;
        for (int i = size - 1; i >= 0; i--) {
            int bit = !(x >> i & 1);
            if (nodes[p][bit] == -1) {
                p = nodes[p][!bit];
            } else {
                result ^= 1ull << i;
                p = nodes[p][bit];
            }
        }
    }

    std::bitset<size> maxXor(std::bitset<size> x) {
        int p = 0;
        std::bitset<size> result;
        for (int i = size - 1; i >= 0; i--) {
            int bit = !x.test(i);
            if (nodes[p][bit] == -1) {
                p = nodes[p][!bit];
            } else {
                result.set(i);
                p = nodes[p][bit];
            }
        }
        return result;
    }

  private:
    std::vector<std::array<int, 2>> nodes;
};

template <mo::internal::traits::Monoid S, bool useLong = true>
class MonoidBinaryTrie {
    using Index = std::conditional<useLong, unsigned long long, unsigned int>;

  public:
    MonoidBinaryTrie() { nodes.emplace_back(S{}); }

    void set(Index idx, S value) {
        int p = 0;
        std::array<int, 64> positions;
        for (int i = 63; i >= 0; i--) {
            positions[i] = p;
            int bit = idx >> i & 1;
            if (nodes[p].child[bit] == -1) {
                nodes[p].child[bit] = nodes.size();
                nodes.emplace_back(S{});
            }
            p = nodes[p].child[bit];
        }
        nodes[p].value = value;
        for (int i : positions) {
            nodes[i].value =
                getValue(nodes[i].child[0]) + getValue(nodes[i].child[1]);
        }
    }

    void add(Index idx, S value) {
        int p = 0;
        std::array<int, 64> positions;
        for (int i = 63; i >= 0; i--) {
            positions[i] = p;
            int bit = idx >> i & 1;
            if (nodes[p][bit] == -1) {
                nodes[p][bit] = nodes.size();
                nodes.emplace_back(S{});
            }
            p = nodes[p][bit];
        }
        nodes[p].value += value;
        for (int i : positions) {
            nodes[i].value =
                getValue(nodes[i].child[0]) + getValue(nodes[i].child[1]);
        }
    }

    S prefixSum(Index idx) {
        int p = 0;
        S ps{};
        for (int i = 63; i >= 0; i--) {
            int bit = idx >> i & 1;
            if (bit) {
                ps += getValue(nodes[p].child[0]);
            }
            p = nodes[p].child[bit];
            if (p == -1) {
                return ps;
            }
        }
        ps += nodes[p].value;
        return ps;
    }

  private:
    struct Node {
        S value;
        int child[2];
        Node(S val) : value(val) { child[0] = child[1] = -1; }
    };

    inline S getValue(int node) {
        if (node == -1) {
            return S{};
        }
        return nodes[node].value;
    }

    std::vector<Node> nodes;
};

}; // namespace mo::internal

#endif
