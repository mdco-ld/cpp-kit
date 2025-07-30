#ifndef _MO_INTERNAL_MONOID_DEQUE_HPP_
#define _MO_INTERNAL_MONOID_DEQUE_HPP_

#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/monoid-stack.hpp>
#include <vector>

namespace mo::internal {

template <traits::Monoid S> class MonoidDeque {
  public:
	void pushRight(S x) {
		right.push(x);
	}
	void pushLeft(S x) {
		left.push(x);
	}
	S popRight() {
		if (!right.size()) {
			balance();
		}
		return right.pop();
	}
	S popLeft() {
		if (!left.size()) {
			balance();
		}
		return left.pop();
	}
	S sum() {
		return left.sum() + right.sum();
	}
	inline int size() {
		return left.size() + right.size();
	}
  private:
	void balance() {
		if (!left.size()) {
			std::vector<S> t;
			while (right.size() > std::ssize(t) + 1) {
				t.push_back(right.pop());
			}
			while (right.size()) {
				left.push(right.pop());
			}
			while (t.size()) {
				right.push(t.back());
				t.pop_back();
			}
		} else if (!right.size()) {
			std::vector<S> t;
			while (left.size() > std::ssize(t) + 1) {
				t.push_back(left.pop());
			}
			while (left.size()) {
				right.push(left.pop());
			}
			while (t.size()) {
				left.push(t.back());
				t.pop_back();
			}
		}
	}

	LeftMonoidStack<S> left;
	RightMonoidStack<S> right;
};

}; // namespace mo::internal

#endif
