#ifndef _MOG_INTERNAL_MATH_LATTICES_HPP_
#define _MOG_INTERNAL_MATH_LATTICES_HPP_

#include <mog/internal/numeric.hpp>

#include <utility>

namespace mog::internal {

namespace lattice {

template <numeric::Integral Int> using Vector = std::pair<Int, Int>;

template <numeric::Integral Int> Int dot(Vector<Int> a, Vector<Int> b) {
	return a.first * b.first + a.second * b.second;
}

template <numeric::Integral Int> Vector<Int> mul(Int a, Vector<Int> b) {
	return {b.first * a, b.second * a};
}

template <numeric::Integral Int> Vector<Int> add(Vector<Int> a, Vector<Int> b) {
	return {a.first + b.first, a.second + b.second};
}

}; // namespace lattice

template <numeric::Integral Int>
std::pair<lattice::Vector<Int>, lattice::Vector<Int>>
reduce2dLattice(lattice::Vector<Int> a, lattice::Vector<Int> b) {
	Int m = 1;
	if (lattice::dot(a, a) > lattice::dot(b, b)) {
		std::swap(a, b);
	}
	while (m != 0) {
		m = lattice::dot(a, b) / lattice::dot(a, a);
		b = lattice::add(b, lattice::mul(-m, a));
		if (lattice::dot(a, a) > lattice::dot(b, b)) {
			std::swap(a, b);
		}
	}
	return {a, b};
}

}; // namespace mog::internal

#endif
