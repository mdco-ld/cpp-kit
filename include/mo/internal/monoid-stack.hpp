#ifndef _MO_INTERNAL_MONOID_STACK_HPP_
#define _MO_INTERNAL_MONOID_STACK_HPP_

#include <mo/internal/concepts/monoid.hpp>
#include <vector>

namespace mo::internal {

template <traits::Monoid S> class LeftMonoidStack {
  public:
	S sum() { return sums.size() ? sums.back() : S{}; }
	S back() { return values.back(); }
	S front() { return values.front(); }
	S operator[](int i) { return values[i]; }
	void push(S x) {
		if (values.empty()) {
			sums.push_back(x);
		} else {
			sums.push_back(x + sums.back());
		}
		values.push_back(x);
	}
	S pop() {
		S ret = values.back();
		sums.pop_back();
		values.pop_back();
		return ret;
	}

	int size() { return values.size(); }

  private:
	std::vector<S> sums;
	std::vector<S> values;
};

template <traits::Monoid S> class RightMonoidStack {
  public:
	S sum() { return sums.size() ? sums.back() : S{}; }
	S back() { return values.back(); }
	S front() { return values.front(); }
	S operator[](int i) { return values[i]; }
	void push(S x) {
		if (values.empty()) {
			sums.push_back(x);
		} else {
			sums.push_back(sums.back() + x);
		}
		values.push_back(x);
	}
	S pop() {
		S ret = values.back();
		sums.pop_back();
		values.pop_back();
		return ret;
	}

	int size() { return values.size(); }

  private:
	std::vector<S> sums;
	std::vector<S> values;
};

}; // namespace mo::internal

#endif
