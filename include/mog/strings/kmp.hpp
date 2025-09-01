#ifndef _MOG_STRINGS_KMP_HPP_
#define _MOG_STRINGS_KMP_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/strings/kmp.hpp>

namespace mog {

template<class T>
inline std::vector<int> kmp(const std::vector<T> &v) {
	return internal::strings::kmp(v);
}

template<class T>
inline std::vector<int> kmp(const std::basic_string<T> &v) {
	return internal::strings::kmp(v);
}

};

#endif
