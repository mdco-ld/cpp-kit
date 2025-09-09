#ifndef _MOG_INTERNAL_SUFFIX_MAX_HPP_
#define _MOG_INTERNAL_SUFFIX_MAX_HPP_

#include <map>

namespace mog::internal {

template <class T, bool (*less)(T, T)> class SuffixMax {
  public:
	void insert(long long x, T value) {
		auto it = suf.lower_bound(x);
		if (it != suf.end() && less(value, it->second)) {
			return;
		}
		while (it != suf.begin() && !less(value, std::prev(it)->second)) {
			it = suf.erase(std::prev(it));
		}
		if (it->first == x) {
			it->second = value;
		} else {
			suf.insert({x, value});
		}
	}
	T max(long long x) {
		auto it = suf.lower_bound(x);
		return it->second;
	}
	T maxOr(long long x, T alternative) {
		auto it = suf.lower_bound(x);
		if (it == suf.end()) {
			return alternative;
		}
		return it->second;
	}
	void clear() { suf.clear(); }

  private:
	std::map<long long, T> suf;
};

}; // namespace mog::internal

#endif
