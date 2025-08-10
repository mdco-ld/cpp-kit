#ifndef _MOG_INTERNAL_HASH_HPP_
#define _MOG_INTERNAL_HASH_HPP_

namespace mog::internal {

using hint = unsigned long long;
using vint = long long;

constexpr hint inv(hint x) {
	hint ans = 1;
	for (int i = 0; i < 64; i++) {
		ans *= x;
		x *= x;
	}
	return ans;
}

template <hint P, hint N> struct Powers {
	constexpr Powers() : powers() {
		powers[0] = 1;
		for (int i = 1; i < N; i++) {
			powers[i] = powers[i - 1] * P;
		}
	}
	constexpr inline hint operator[](int i) { return powers[i]; }
	hint powers[N];
};

template <hint P, hint N = 0ull> class Hash {
	static constexpr hint Q = inv(P);
	static constexpr Powers<P, N> powerP = Powers<P, N>{};
	static constexpr Powers<Q, N> powerQ = Powers<P, N>{};
	hint x;

  public:
	Hash() { x = 0; }
	Hash(vint value) { x = value < 0 ? powerQ[-value] : powerP[value]; }
	Hash operator+(const Hash other) const { return Hash{x + other.x}; }
	Hash operator-(const Hash other) const { return Hash{x - other.x}; }
	Hash &operator+=(const Hash other) {
		*this = *this + other;
		return *this;
	}
	Hash &operator-=(const Hash other) {
		*this = *this - other;
		return *this;
	}
	Hash shift(vint value) const { return Hash{x * Hash(value).x}; }
	inline bool operator==(const Hash other) const { return x == other.x; }
	inline hint value() { return x; }
};

template <unsigned long long P> class Hash<P, 0ull> {
	static constexpr hint Q = inv(P);
	hint x;

	inline static Hash raw(hint value) {
		Hash result;
		result.x = value;
		return result;
	}

  public:
	Hash() { x = 0; }
	Hash(vint value) {
		x = 1;
		hint base = P;
		if (value < 0) {
			value = -value;
			base = Q;
		}
		while (value) {
			if (value & 1) {
				x *= base;
			}
			value >>= 1;
			base *= base;
		}
	}
	Hash operator+(const Hash other) const { return Hash::raw(x + other.x); }
	Hash operator-(const Hash other) const { return Hash::raw(x - other.x); }
	Hash &operator+=(const Hash other) {
		*this = *this + other;
		return *this;
	}
	Hash &operator-=(const Hash other) {
		*this = *this - other;
		return *this;
	}
	Hash shift(vint value) const { return Hash::raw(x * Hash(value).x); }
	inline bool operator==(const Hash other) const { return x == other.x; }
	inline hint value() { return x; }
};

template <hint P, hint Q, vint Nx = 0ull, vint Ny = 0ull> class Hash2 {
	hint x;
	using hashP = Hash<P, Nx>;
	using hashQ = Hash<Q, Ny>;

	inline static Hash2 raw(hint value) {
		Hash2 result;
		result.x = value;
		return result;
	}

  public:
	Hash2() : x(0) {}
	Hash2(vint valueX, vint valueY)
		: x(hashP(valueX).value() * hashQ(valueY).value()) {}
	Hash2 operator+(const Hash2 other) const {
		return Hash2::raw(x + other.x);
	};
	Hash2 &operator+=(const Hash2 other) {
		*this = *this + other;
		return *this;
	}
	Hash2 operator-(const Hash2 other) const { return Hash2::raw(x - other.x); }
	Hash2 &operator-=(const Hash2 other) {
		*this = *this - other;
		return *this;
	}
	inline bool operator==(const Hash2 other) const { return x == other.x; }
	Hash2 shiftX(vint value) const {
		return Hash2::raw(x * hashP(value).value());
	}
	Hash2 shiftY(vint value) const {
		return Hash2::raw(x * hashQ(value).value());
	}
	Hash2 shift(vint valueX, vint valueY) const {
		return Hash2::raw(x * hashP(valueX).value() * hashQ(valueY).value());
	}
	inline hint value() { return x; }
};

template <hint P, hint Q, hint R, vint Nx = 0, vint Ny = 0, vint Nz = 0>
class Hash3 {
	hint x;

	using hashP = Hash<P, Nx>;
	using hashQ = Hash<Q, Ny>;
	using hashR = Hash<R, Nz>;

	inline static Hash3 raw(vint value) {
		Hash3 result;
		result.x = value;
		return result;
	}

  public:
	Hash3() : x(0) {}
	Hash3(vint valueX, vint valueY, vint valueZ)
		: x(hashP(valueX).value() * hashQ(valueY).value() *
			hashR(valueZ).value()) {}
	Hash3 operator+(const Hash3 other) const {
		return Hash3{
			x + other.x,
		};
	};
	Hash3 &operator+=(const Hash3 other) {
		*this = *this + other;
		return *this;
	}
	Hash3 operator-(const Hash3 other) const {
		return Hash3{
			x - other.x,
		};
	}
	Hash3 &operator-=(const Hash3 other) {
		*this = *this - other;
		return *this;
	}
	Hash3 shiftX(vint value) const { return Hash3::raw(x * hashP(value)); }
	Hash3 shiftY(vint value) const { return Hash3::raw(x * hashQ(value)); }
	Hash3 shiftZ(vint value) const { return Hash3::raw(x * hashR(value)); }
	Hash3 shift(vint valueX, vint valueY, vint valueZ) const {
		return Hash3::raw(x * hashP(valueX).value() * hashQ(valueY).value() *
						  hashR(valueZ).value());
	}
	hint value() { return x; }
};

template <hint P, hint Q, vint N = 0> class OrderedHash {
	Hash2<P, Q, N, 0> h;
	int cnt;

  public:
	OrderedHash() : h(), cnt(0) {}
	OrderedHash(vint value, int count) : h(value, count), cnt(count) {}
	OrderedHash(vint value) : OrderedHash(value, 1) {}
	OrderedHash operator+(const OrderedHash other) const {
		OrderedHash result = *this;
		result.h += other.h.shiftY(cnt);
		result.cnt += other.cnt;
		return result;
	}
	OrderedHash &operator+=(const OrderedHash other) {
		*this = *this + other;
		return *this;
	}
	inline bool operator==(const OrderedHash other) const {
		return h == other.h && cnt == other.cnt;
	}
	hint value() { return h.value(); }
	int size() { return cnt; }
};

}; // namespace mog::internal

#endif
