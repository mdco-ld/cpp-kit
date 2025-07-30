#ifndef _MO_INTERNAL_MONOID_QUEUE_HPP_
#define _MO_INTERNAL_MONOID_QUEUE_HPP_

#include <mo/internal/concepts/monoid.hpp>
#include <mo/internal/monoid-stack.hpp>

namespace mo::internal {

template <traits::Monoid S> class MonoidQueue {
  public:
	void push(S x) {
		right.push(x);
	}
	S pop() {
		if (!left.size()) {
			while (right.size()) {
				left.push(right.pop());
			}
		}
		return left.pop();
	}
	S sum() {
		return left.sum() + right.sum();
	}
	int size() {
		return left.size() + right.size();
	}
  private:
	LeftMonoidStack<S> left;
	RightMonoidStack<S> right;
};

template <traits::Monoid S> class ReverseMonoidQueue {
  public:
	void push(S x) {
		left.push(x);
	}
	S pop() {
		if (!right.size()) {
			while (left.size()) {
				right.push(left.pop());
			}
		}
		return right.pop();
	}
	S sum() {
		return left.sum() + right.sum();
	}
	int size() {
		return right.size() + left.size();
	}
  private:
	LeftMonoidStack<S> left;
	RightMonoidStack<S> right;
};

}; // namespace mo::internal

#endif
