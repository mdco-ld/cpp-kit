#ifndef _MOG_INTERNAL_SEGMENT_STACK_HPP_
#define _MOG_INTERNAL_SEGMENT_STACK_HPP_

#include <mog/internal/concepts/monoid.hpp>
#include <vector>

namespace mog::internal {

template <traits::Monoid S> class SegmentStack {
  public:
	SegmentStack() : lift(1, 0), value(1, S{}), liftValue(1, S{}), n(0) {}
	void push(S x) {
		value.push_back(x);
		if (n - lift[n] == lift[n] - lift[lift[n]]) {
			lift.push_back(lift[lift[n]]);
			liftValue.push_back(liftValue[lift[n]] + liftValue[n] + x);
		} else {
			lift.push_back(n);
			liftValue.push_back(x);
		}
		n++;
	}
	S pop() {
		S ret = value.back();
		if (n > 0) {
			lift.pop_back();
			value.pop_back();
			liftValue.pop_back();
			n--;
		}
		return ret;
	}
	S sum() {
		S result{};
		for (int r = n; r > 0; r = lift[r]) {
			result = liftValue[r] + result;
		}
		return result;
	}

	S sum(int l, int r) {
		S result{};
		while (r > l) {
			if (lift[r] >= l) {
				result = liftValue[r] + result;
				r = lift[r];
			} else {
				result = value[r] + result;
				r--;
			}
		}
		return result;
	}

  private:
	std::vector<int> lift;
	std::vector<S> value;
	std::vector<S> liftValue;
	int n;
};

}; // namespace mog::internal

#endif
