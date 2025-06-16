#ifndef _MO_MATH_GAUSSIAN_ELIMINATION_HPP_
#define _MO_MATH_GAUSSIAN_ELIMINATION_HPP_

#include <mo/math/field.hpp>
#include <mo/math/matrix.hpp>

#include <algorithm>
#include <vector>

namespace mo {

namespace math {

template <Field F>
void gaussianElimination(DynMatrix<F> &mat,
                         std::vector<typename F::ValueType> &v) {
    using Elem = typename F::ValueType;
    constexpr auto plus = F::plus;
    constexpr auto mul = F::mul;
    constexpr auto neg = F::neg;
    constexpr auto inv = F::inv;

    int n = mat.rows();
    int m = mat.cols();

    for (int row = 0, col = 0; col < m && row < n;) {
        if (mat[row][col] == F::zero()) {
            for (int i = row + 1; i < n; i++) {
                if (mat[i][col] != F::zero()) {
                    std::swap(mat[row], mat[i]);
                    std::swap(v[row], v[i]);
                    break;
                }
            }
            if (mat[row][col] == F::zero()) {
                col++;
                continue;
            }
        }
        if (mat[row][col] != F::one()) {
            Elem pivotInv = inv(mat[row][col]);
            for (int j = col; j < m; j++) {
                mat[row][j] = mul(mat[row][j], pivotInv);
            }
            v[row] = mul(v[row], pivotInv);
        }
        for (int i = 0; i < n; i++) {
            if (i == row || mat[i][col] == F::zero()) {
                continue;
            }
            Elem q = neg(mat[i][col]);
            for (int j = col; j < m; j++) {
                mat[i][j] = plus(mat[i][j], mul(mat[row][j], q));
            }
            v[i] = plus(v[i], mul(v[row], q));
        }
        row++;
        col++;
    }
}

/**
 * Performs inline gaussian elimination
 */
template <Field F, int N, int M>
void gaussianElimination(Matrix<F, N, M> &mat,
                         std::vector<typename F::ValueType> &v) {
    using Elem = typename F::ValueType;
    constexpr auto plus = F::plus;
    constexpr auto mul = F::mul;
    constexpr auto neg = F::neg;
    constexpr auto inv = F::inv;

    constexpr int n = mat.rows();
    constexpr int m = mat.cols();

    for (int row = 0, col = 0; col < m && row < n;) {
        if (mat[row][col] == F::zero()) {
            for (int i = row + 1; i < n; i++) {
                if (mat[i][col] != F::zero()) {
                    std::array<Elem, n> tmp;
                    std::copy(mat[i].begin(), mat[i].end(), tmp.begin());
                    std::copy(mat[row].begin(), mat[row].end(), mat[i].begin());
                    std::copy(tmp.begin(), tmp.end(), mat[row].begin());
                    std::swap(v[row], v[i]);
                    break;
                }
            }
            if (mat[row][col] == F::zero()) {
                col++;
                continue;
            }
        }
        if (mat[row][col] != F::one()) {
            Elem pivotInv = inv(mat[row][col]);
            for (int j = col; j < m; j++) {
                mat[row][j] = mul(mat[row][j], pivotInv);
            }
            v[row] = mul(v[row], pivotInv);
        }
        for (int i = 0; i < n; i++) {
            if (i == row || mat[i][col] == F::zero()) {
                continue;
            }
            Elem q = neg(mat[i][col]);
            for (int j = col; j < m; j++) {
                mat[i][j] = plus(mat[i][j], mul(mat[row][j], q));
            }
            v[i] = plus(v[i], mul(v[row], q));
        }
        row++;
        col++;
    }
}

template <Field F> F::ValueType gaussianElimination(DynMatrix<F> &mat) {
    using Elem = typename F::ValueType;
    constexpr auto plus = F::plus;
    constexpr auto mul = F::mul;
    constexpr auto neg = F::neg;
    constexpr auto inv = F::inv;

    Elem ret = F::one();

    int n = mat.rows();
    int m = mat.cols();

    for (int row = 0, col = 0; col < m && row < n;) {
        if (mat[row][col] == F::zero()) {
            for (int i = row + 1; i < n; i++) {
                if (mat[i][col] != F::zero()) {
                    std::swap(mat[row], mat[i]);
                    ret = neg(ret);
                    break;
                }
            }
            if (mat[row][col] == F::zero()) {
                col++;
                continue;
            }
        }
        if (mat[row][col] != F::one()) {
            Elem pivotInv = inv(mat[row][col]);
            ret = mul(ret, mat[row][col]);
            for (int j = col; j < m; j++) {
                mat[row][j] = mul(mat[row][j], pivotInv);
            }
        }
        for (int i = 0; i < n; i++) {
            if (i == row || mat[i][col] == F::zero()) {
                continue;
            }
            Elem q = neg(mat[i][col]);
            for (int j = col; j < m; j++) {
                mat[i][j] = plus(mat[i][j], mul(mat[row][j], q));
            }
        }
        row++;
        col++;
    }
    return ret;
}

template <Field F, int N, int M>
F::ValueType gaussianElimination(Matrix<F, N, M> &mat) {
    using Elem = typename F::ValueType;
    constexpr auto plus = F::plus;
    constexpr auto mul = F::mul;
    constexpr auto neg = F::neg;
    constexpr auto inv = F::inv;

    Elem ret = F::one();

    constexpr int n = mat.rows();
    constexpr int m = mat.cols();

    for (int row = 0, col = 0; col < m && row < n;) {
        if (mat[row][col] == F::zero()) {
            for (int i = row + 1; i < n; i++) {
                if (mat[i][col] != F::zero()) {
                    std::array<Elem, n> tmp;
                    std::copy(mat[i].begin(), mat[i].end(), tmp.begin());
                    std::copy(mat[row].begin(), mat[row].end(), mat[i].begin());
                    std::copy(tmp.begin(), tmp.end(), mat[row].begin());
                    ret = neg(ret);
                    break;
                }
            }
            if (mat[row][col] == F::zero()) {
                col++;
                continue;
            }
        }
        if (mat[row][col] != F::one()) {
            Elem pivotInv = inv(mat[row][col]);
            ret = mul(ret, mat[row][col]);
            for (int j = col; j < m; j++) {
                mat[row][j] = mul(mat[row][j], pivotInv);
            }
        }
        for (int i = 0; i < n; i++) {
            if (i == row || mat[i][col] == F::zero()) {
                continue;
            }
            Elem q = neg(mat[i][col]);
            for (int j = col; j < m; j++) {
                mat[i][j] = plus(mat[i][j], mul(mat[row][j], q));
            }
        }
        row++;
        col++;
    }
	return ret;
}

}; // namespace math

}; // namespace mo

#endif
