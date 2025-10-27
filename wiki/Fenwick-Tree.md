The `mog::FenwickTree<S>` class maintains an array of elements, and supports calculating the sum of the elements in a prefix in $O(\log(N))$, as well as adding to the value at a specific index in $O(\log(N))$. `S` is assumed to be a [monoid](https://github.com/mdco-ld/cpp-kit/wiki/Concepts#monoid).

# Methods

## Constructor
```cpp
FenwickTree(int N)
```
Constructs a Fenwick Tree of size `N`, where each element is initialized as the neutral element for the monoid S.

## `add`
```cpp
void add(int idx, S value)
```
### Description

Adds `value` to the element at index `idx`.

### Time Complexity
$O(\log(N))$.

## `prefixSum`
```cpp
S prefixSum(int r)
```
### Description

Calculates the sum of the elements in the range $[0, r)$.

### Time Complexity
$O(\log(N))$.

## `sum`
```cpp
S sum(int l, int r)
```
### Description

Calculates the sum of the elements in the range $[l, r)$.

**Requires `S` to be a [group](https://github.com/mdco-ld/cpp-kit/wiki/Concepts#group)**.

### Time Complexity
$O(\log(N))$.