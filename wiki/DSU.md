The `mog::DSU` class (Disjoint Set Union, also known as Union-Find) maintains a collection of disjoint sets and supports efficiently merging sets and checking if two elements belong to the same set. Both operations run in amortized $O(\alpha(N))$ time, where $\alpha$ is the inverse Ackermann function (effectively constant for practical purposes).

# Methods

## Constructor
```cpp
DSU(int N)
```
Constructs a DSU with `N` elements, where each element is initially in its own set.

## `root`
```cpp
int root(int x)
```
### Description

Returns the representative (root) element of the set containing `x`. Uses path compression for efficiency.

### Time Complexity
Amortized $O(\alpha(N))$.

## `merge`
```cpp
bool merge(int x, int y)
```
### Description

Merges the sets containing `x` and `y`. Returns `true` if the sets were different and were merged, `false` if they were already in the same set.

### Time Complexity
Amortized $O(\alpha(N))$.

## `same`
```cpp
bool same(int x, int y)
```
### Description

Returns `true` if elements `x` and `y` belong to the same set, `false` otherwise.

### Time Complexity
Amortized $O(\alpha(N))$.
