#ifndef _MO_MATH_MATRIX_HPP_
#define _MO_MATH_MATRIX_HPP_

#include <array>
#include <mo/math/group.hpp>
#include <mo/math/monoid.hpp>
#include <mo/math/ring.hpp>
#include <mo/math/semiring.hpp>

#include <cstdint>
#include <vector>

namespace mo {

namespace math {

template <Monoid T> class DynMatrix {
  public:
    DynMatrix(int N, int M)
        : values(N, std::vector<typename T::ValueType>(M, T::zero())), n(N),
          m(M), isSquare(N == M) {
    }

    static DynMatrix identity(int n)
        requires(Semiring<T>)
    {
        DynMatrix result(n, n);
        for (int i = 0; i < n; i++) {
            result.values[i][i] = T::one();
        }
        return result;
    }

    DynMatrix operator+(const DynMatrix &other) const {
        DynMatrix result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.values[i][j] = T::plus(values[i][j], other.values[i][j]);
            }
        }
        return result;
    }

    DynMatrix operator-(const DynMatrix &other) const
        requires(Group<T>)
    {
        DynMatrix result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.values[i][j] =
                    T::plus(values[i][j], T::neg(other.values[i][j]));
            }
        }
        return result;
    }

    DynMatrix operator-() const
        requires(Group<T>)
    {
        DynMatrix result(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result.values[i][j] = T::neg(values[i][j]);
            }
        }
        return result;
    }

    DynMatrix operator*(const DynMatrix &other) const
        requires(Semiring<T>)
    {
        DynMatrix result(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < other.m; j++) {
                for (int k = 0; k < m; k++) {
                    result.values[i][j] =
                        T::mul(values[i][k], other.values[k][j]);
                }
            }
        }
        return result;
    }

    DynMatrix pow(int64_t e) const
        requires(Semiring<T>)
    {
        DynMatrix result = identity(n);
        DynMatrix base = *this;
        while (e > 0) {
            if (e & 1) {
                result = result * base;
            }
            e >>= 1;
            base = base * base;
        }
        return result;
    }

    inline int rows() const { return n; }

    inline int cols() const { return m; }

    inline std::vector<typename T::ValueType> &operator[](int i) {
        return values[i];
    }

  private:
    std::vector<std::vector<typename T::ValueType>> values;
    int n;
    int m;
    const bool isSquare;
};

template <Monoid T, int N, int M = N> class Matrix {
    static_assert(N > 0);
    static_assert(M > 0);

    static constexpr bool isSquare = N == M;

  public:
    Matrix() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                values[i][j] = T::zero();
            }
        }
    }

    static Matrix identity() {
        static_assert(N == M);
        Matrix result(N, M);
        for (int i = 0; i < N; i++) {
            result.values[i][i] = T::one();
        }
        return result;
    }

    Matrix operator+(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result.values[i][j] = T::plus(values[i][j], other.values[i][j]);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const
        requires(Group<T>)
    {
        Matrix result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result.values[i][j] =
                    T::plus(values[i][j], T::neg(other.values[i][j]));
            }
        }
        return result;
    }

    Matrix operator-() const
        requires(Group<T>)
    {
        Matrix result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result.values[i][j] = T::neg(values[i][j]);
            }
        }
        return result;
    }

    template <int K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K> &other) const
        requires(Semiring<T>)
    {
        Matrix<T, N, K> result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < K; j++) {
                for (int k = 0; k < M; k++) {
                    result.values[i][j] =
                        T::mul(values[i][k], other.values[k][j]);
                }
            }
        }
        return result;
    }

    Matrix pow(int64_t e) const
        requires(Semiring<T>)
    {
        static_assert(isSquare);
        Matrix result = identity();
        Matrix base = *this;
        while (e > 0) {
            if (e & 1) {
                result = result * base;
            }
            e >>= 1;
            base = base * base;
        }
        return result;
    }

    std::array<typename T::ValueType, M> &operator[](int i) {
        return values[i];
    }

    constexpr int rows() const { return N; }
    constexpr int cols() const { return M; }

  private:
    std::array<std::array<typename T::ValueType, M>, N> values;
};

}; // namespace math

}; // namespace mo

#endif
