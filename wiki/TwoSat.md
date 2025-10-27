The `mog::TwoSat` class solves the 2-SAT (2-satisfiability) problem, which determines whether a boolean formula in conjunctive normal form with at most 2 literals per clause can be satisfied. The algorithm runs in $O(N + M)$ time, where $N$ is the number of variables and $M$ is the number of clauses.

# Methods

## Constructor
```cpp
TwoSat(int N)
```
Constructs a 2-SAT solver for `N` boolean variables (indexed from $0$ to $N-1$).

## `addClause`
```cpp
void addClause(int x, bool vx, int y, bool vy)
```
### Description

Adds a clause $(x_{\text{vx}} \lor y_{\text{vy}})$ to the formula. If `vx` is `true`, the clause uses the positive literal of variable `x`, otherwise it uses the negation. The same applies to `vy` and variable `y`.

### Time Complexity
$O(1)$.

## `solve`
```cpp
bool solve()
```
### Description

Attempts to find a satisfying assignment for the formula. Returns `true` if the formula is satisfiable, `false` otherwise.

### Time Complexity
$O(N + M)$, where $N$ is the number of variables and $M$ is the number of clauses.

## `solution`
```cpp
const std::vector<bool>& solution()
```
### Description

Returns a satisfying assignment as a vector of boolean values. Should only be called after `solve()` returns `true`. The value at index `i` represents the assignment to variable `i`.

### Time Complexity
$O(1)$.
