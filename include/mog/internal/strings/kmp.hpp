#ifndef _MOG_INTERNAL_STRINGS_KMP_HPP_
#define _MOG_INTERNAL_STRINGS_KMP_HPP_

#include <string>
#include <vector>

namespace mog::internal::strings {

template <class T> std::vector<int> kmp(const std::vector<T> &v) {
	int n = std::ssize(v);
	int pre = 0;
	std::vector<int> ret(n);
	for (int i = 1; i < n; i++) {
		while (v[i] != v[pre] && pre > 0) {
			pre = ret[pre];
		}
		if (v[i] == v[pre]) {
			ret[i] = ++pre;
		}
	}
	return ret;
}

template <class T> std::vector<int> kmp(const std::basic_string<T> &v) {
	int n = std::ssize(v);
	int pre = 0;
	std::vector<int> ret(n);
	for (int i = 1; i < n; i++) {
		while (v[i] != v[pre] && pre > 0) {
			pre = ret[pre];
		}
		if (v[i] == v[pre]) {
			ret[i] = ++pre;
		}
	}
	return ret;
}

}; // namespace mog::internal::strings

#endif
