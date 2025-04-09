#ifndef _MO_MATH_DETERMINANT_HPP_
#define _MO_MATH_DETERMINANT_HPP_

#include <mo/math/gaussian-elimination.hpp>
#include <mo/math/matrix.hpp>

namespace mo {

namespace math {

template <Field F> F::ValueType determinant(const DynMatrix<F> &mat) {
    using Elem = typename F::ValueType;

    assert(mat.rows() == mat.cols());
    DynMatrix m = mat;
    Elem det = gaussianElimination(m);
    int n = m.rows();
    for (int i = 0; i < n; i++) {
        det = F::mul(det, m[i][i]);
    }
    return det;
}

}; // namespace math

}; // namespace mo

#endif
