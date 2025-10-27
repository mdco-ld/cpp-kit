The `mog::ModInt<mod>` template class provides modular arithmetic operations with a compile-time modulus. It supports addition, subtraction, multiplication, division, and exponentiation modulo `mod`.

The library provides predefined type aliases:
- `mog::Int1e9p7` for modulo $10^9+7$
- `mog::Int998244353` for modulo $998244353$
- `mog::Int2` for modulo $2$

# Methods

## Constructor
```cpp
ModInt(int value = 0)
```
Constructs a `ModInt` with the given value, automatically taken modulo `mod`.

## Arithmetic Operators
```cpp
ModInt operator+(const ModInt& other) const
ModInt operator-(const ModInt& other) const
ModInt operator*(const ModInt& other) const
ModInt operator/(const ModInt& other) const
```
### Description

Performs the corresponding arithmetic operation modulo `mod`. Division is computed as multiplication by the modular inverse (requires `mod` to be prime and `other` to be non-zero).

### Time Complexity
$O(1)$ for addition, subtraction, and multiplication. $O(\log(\text{mod}))$ for division (due to inverse computation).

## Compound Assignment Operators
```cpp
ModInt& operator+=(const ModInt& other)
ModInt& operator-=(const ModInt& other)
ModInt& operator*=(const ModInt& other)
ModInt& operator/=(const ModInt& other)
```
### Description

Performs the corresponding arithmetic operation in-place.

### Time Complexity
$O(1)$ for `+=`, `-=`, and `*=`. $O(\log(\text{mod}))$ for `/=`.

## `pow`
```cpp
ModInt pow(long long exp) const
```
### Description

Computes this value raised to the power `exp` modulo `mod` using binary exponentiation.

### Time Complexity
$O(\log(\text{exp}))$.

## `inv`
```cpp
ModInt inv() const
```
### Description

Computes the modular multiplicative inverse. Requires `mod` to be prime and the value to be non-zero.

### Time Complexity
$O(\log(\text{mod}))$.
