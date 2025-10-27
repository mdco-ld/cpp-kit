The `mog::SegmentTree<S>` class maintains an array of the elements in the monoid `S`, and supports calculating the sum of the elements in a range $[l, r)$ in $O(\log(N))$ time, as well as changing the value at any position in $O(\log(N))$ time.

# Methods

## `set`
```cpp
void set(int i, S value)
```
### Description

Changes the value at position `i` to `value`.

### Time Complexity
$O(\log(N))$

## `sum`
```cpp
S sum(int l, int r)
```
### Description

Calculates the sum of the values in the range $[l, r)$.

### Time Complexity
$O(\log(N))$