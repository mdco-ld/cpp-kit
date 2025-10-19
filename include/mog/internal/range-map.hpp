#ifndef _MOG_INTERNAL_RANGE_MAP_HPP_
#define _MOG_INTERNAL_RANGE_MAP_HPP_

#include <map>

namespace mog::internal {

template <class Key, class Value, Value (*id)()> class RangeMap {
  public:
	void clear() { mp.clear(); }

	void set(Key l, Key r, Value val) {
		Value rval = get(r);
		for (auto it = mp.lower_bound(l); it != mp.end() && it->first < r;
			 it = mp.erase(it)) {
		}
		mp.insert({l, val});
		mp.insert({r, rval});
	}

	Value get(Key i) {
		if (mp.empty()) {
			return id();
		}
		auto it = mp.upper_bound(i);
		if (it == mp.begin()) {
			return id();
		}
		return std::prev(it)->second;
	}

  private:
	std::map<Key, Value> mp;
};

}; // namespace mog::internal

#endif
