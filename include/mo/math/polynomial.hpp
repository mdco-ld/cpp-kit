#ifndef _MO_MATH_POLYNOMIAL_HPP_
#define _MO_MATH_POLYNOMIAL_HPP_

#include <mo/math/fft.hpp>
#include <mo/math/field.hpp>

#include <vector>

namespace mo {

namespace math {

template <Field F> class Polynomial {
  public:
    using ValueType = typename F::ValueType;

    Polynomial() : coefs(), n(0) {}

    Polynomial(std::initializer_list<ValueType> c) : coefs(c), n(c.size()) {
        while (coefs.size() > 0 && coefs.back() == F::zero()) {
            coefs.pop_back();
        }
        n = coefs.size();
    }

    Polynomial(std::vector<ValueType> &v) : coefs(v), n(v.size()) {
        while (coefs.size() > 0 && coefs.back() == F::zero()) {
            coefs.pop_back();
        }
        n = coefs.size();
    }

    Polynomial(std::vector<ValueType> &&v) : coefs(v), n(v.size()) {
        while (coefs.size() > 0 && coefs.back() == F::zero()) {
            coefs.pop_back();
        }
        n = coefs.size();
    }

    ValueType eval(ValueType x) const {
        ValueType result = F::zero();
        int n = coefs.size();
        ValueType base = F::one();
        for (int i = 0; i < n; i++) {
            result = F::plus(result, F::mul(coefs[i], base));
            base = F::mul(base, x);
        }
    }

    Polynomial operator+(const Polynomial &p) const {
        int m = std::max(n, p.n);
        std::vector<ValueType> result(m);
        for (int i = 0; i < m; i++) {
            if (i >= n) {
                result[i] = p.coefs[i];
            } else if (i >= p.n) {
                result[i] = coefs[i];
            } else {
                result[i] = F::plus(coefs[i], p.coefs[i]);
            }
        }
        return Polynomial(std::move(result));
    }

    Polynomial operator+=(const Polynomial &other) {
        while (coefs.size() < other.coefs.size()) {
            coefs.push_back(F::zero());
        }
        for (int i = 0; i < std::min(n, other.n); i++) {
            coefs[i] = F::plus(coefs[i], other.coefs[i]);
        }
    }

	Polynomial operator*=(const Polynomial &other) {
		*this = (*this) * other;
	}

    Polynomial operator-(const Polynomial &p) const {
        int m = std::max(n, p.n);
        std::vector<ValueType> result(m);
        for (int i = 0; i < m; i++) {
            if (i > n) {
                result[i] = p.coefs[i];
            } else if (i > p.n) {
                result[i] = F::neg(coefs[i]);
            } else {
                result[i] = F::plus(coefs[i], F::neg(p.coefs[i]));
            }
        }
        return Polynomial(std::move(result));
    }

    Polynomial operator-() const {
        std::vector<ValueType> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = F::neg(coefs[i]);
        }
        return Polynomial(std::move(result));
    }

    Polynomial operator*(const Polynomial &p) const {
        if (coefs.size() == 0) {
            return *this;
        }
        if (p.coefs.size() == 0) {
            return p;
        }
        std::vector<ValueType> result =
            mo::math::convolution<F>(coefs, p.coefs);
        return Polynomial(std::move(result));
    }

    bool operator==(const Polynomial &p) const {
        if (coefs.size() == 0) {
            return p.coefs.size() == 0;
        }
        if (deg() != p.deg()) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (coefs[i] != p.coefs[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const Polynomial &&p) const {
        if (coefs.size() == 0) {
            return p.coefs.size() == 0;
        }
        if (deg() != p.deg()) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (coefs[i] != p.coefs[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Polynomial &p) const {
        if (coefs.size() == 0) {
            return p.coefs.size() != 0;
        }
        if (deg() != p.deg()) {
            return true;
        }
        for (int i = 0; i < n; i++) {
            if (coefs[i] != p.coefs[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator!=(const Polynomial &&p) const {
        if (coefs.size() == 0) {
            return p.coefs.size() != 0;
        }
        if (deg() != p.deg()) {
            return true;
        }
        for (int i = 0; i < n; i++) {
            if (coefs[i] != p.coefs[i]) {
                return true;
            }
        }
        return false;
    }

    inline int deg() const { return std::max(n - 1, 0); }

    inline ValueType coef(int i) const { return coefs[i]; }

  private:
    std::vector<ValueType> coefs;
    int n;
};

}; // namespace math

}; // namespace mo

#endif
