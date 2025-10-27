# Monoid
Represents a monoid, where the neutral element is given by the default constructor.
It is assumed to have `operator+` with the same type, and `operator+` is also assumed to be associative.

# Group
Represents a mathematical group, where the neutral element is given by the default constructor.
It is assumed to have `operator+`, `operator-` with the same type. `operator+` is assumed to be associative, and `operator-` is assumed to be the inverse operation of `operator+`.

# Semiring
Represents a semiring using `operator+` and `operator*`.
In this library, it is assumed that the identity element for the `operator+` can be obtained as `S(0)` (constructor with int), and the identity element for the `operator*` can be obtained with `S(1)` (constructor with int).

# Ring
Same as Semiring, but assumes that the `operator+` has an inverse operation represented by `operator-`.