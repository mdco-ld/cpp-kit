#ifndef _MOG_INTERNAL_MATH_MATRIX_HPP_
#define _MOG_INTERNAL_MATH_MATRIX_HPP_

#include <array>
#include <mog/internal/concepts/ring.hpp>

namespace mog::internal::math {

template <traits::Semiring S, int N, int M = N> class MatrixN {
  private:
	std::array<std::array<S, M>, N> e;

  public:
	static constexpr MatrixN identity() {
		static_assert(N == M);
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) {
					result.e[i][j] = S{1};
				} else {
					result.e[i][j] = S{};
				}
			}
		}
		return result;
	}
	static constexpr MatrixN zero() {
		static_assert(N == M);
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = S{};
			}
		}
		return result;
	}
	constexpr MatrixN() = default;

	constexpr MatrixN(int x) {
		if (x) {
			*this = identity();
		} else {
			*this = zero();
		}
	}

	constexpr std::array<S, M> &operator[](int i) { return e[i]; }

	constexpr MatrixN operator+(const MatrixN other) const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = e[i][j] + other.e[i][j];
			}
		}
		return result;
	}

	constexpr MatrixN operator-(const MatrixN other) const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = e[i][j] - other.e[i][j];
			}
		}
		return result;
	}

	constexpr MatrixN &operator+=(const MatrixN other) {
		*this = (*this) + other;
		return *this;
	}

	constexpr MatrixN &operator-=(const MatrixN other) {
		*this = (*this) - other;
		return *this;
	}

	constexpr MatrixN operator-() const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = -e[i][j];
			}
		}
		return result;
	}

	template <int K>
	constexpr MatrixN<S, N, K> operator*(const MatrixN<S, M, K> other) const {
		MatrixN<S, N, K> result = zero();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < K; j++) {
				for (int k = 0; k < M; k++) {
					result.e[i][j] += e[i][k] * other.e[k][j];
				}
			}
		}
		return result;
	}

	constexpr MatrixN &operator*=(const MatrixN other) {
		*this = (*this) * other;
		return *this;
	}

	constexpr MatrixN pow(long long x) {
		MatrixN result = identity();
		MatrixN base = *this;
		while (x) {
			if (x & 1) {
				result = result * base;
			}
			base = base * base;
			x >>= 1;
		}
		return result;
	}
};

}; // namespace mog::internal::math

#endif
