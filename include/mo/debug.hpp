#ifndef _MO_DEBUG_HPP_
#define _MO_DEBUG_HPP_

#include <iostream>
#include <vector>

template <typename T> void __dbg2(T t) { std::cerr << t; }
template <> inline void __dbg2(bool t) { std::cerr << (t ? "true" : "false"); }
template<typename T> void __dbg2(std::vector<T> &v) {
	std::cerr << "[";
	for (int i = 0; i < v.size(); i++) {
		std::cerr << v[i];
		if (i + 1 < v.size()) {
			std::cerr << ", ";
		}
	}
	std::cerr << "]";
}
inline void __dbg() { std::cerr << std::endl; }
template <typename T> void __dbg(T t) {
    __dbg2(t);
    std::cerr << std::endl;
}
template <typename T, typename... TRest> void __dbg(T first, TRest... rest) {
    __dbg2(first);
    std::cerr << ", ";
    __dbg(rest...);
}
#define dbg(...)                                                               \
    do {                                                                       \
        std::cerr << "DBG> " << "(" << #__VA_ARGS__ << ") = ";                 \
        __dbg(__VA_ARGS__);                                                    \
    } while (0)

#endif
