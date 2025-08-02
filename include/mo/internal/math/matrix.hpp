#ifndef _MO_INTERNAL_MATH_MATRIX_HPP_
#define _MO_INTERNAL_MATH_MATRIX_HPP_

#include <array>
#include <mo/internal/concepts/ring.hpp>
#include <vector>

namespace mo::internal::math {

template <traits::Semiring S, int N, int M = N> class MatrixN {
  private:
	std::array<std::array<S, M>, N> e;

  public:
	static MatrixN identity() {
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
	static MatrixN zero() {
		static_assert(N == M);
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = S{};
			}
		}
		return result;
	}
	MatrixN() = default;
	
	MatrixN(int x) {
		if (x) {
			*this = identity();
		} else {
			*this = zero();
		}
	}

	std::array<S, M> &operator[](int i) { return e[i]; }

	MatrixN operator+(const MatrixN other) const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = e[i][j] + other.e[i][j];
			}
		}
		return result;
	}


	MatrixN operator-(const MatrixN other) const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = e[i][j] - other.e[i][j];
			}
		}
		return result;
	}

	MatrixN &operator+=(const MatrixN other) {
		*this = (*this) + other;
		return *this;
	}

	MatrixN &operator-=(const MatrixN other) {
		*this = (*this) - other;
		return *this;
	}

	MatrixN operator-() const {
		MatrixN result;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				result.e[i][j] = -e[i][j];
			}
		}
		return result;
	}

	template <int K>
	MatrixN<S, N, K> operator*(const MatrixN<S, M, K> other) const {
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

	MatrixN &operator*=(const MatrixN other) {
		*this = (*this) * other;
		return *this;
	}

	MatrixN pow(long long x) {
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

}; // namespace mo::internal::math

#endif
