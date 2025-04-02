#ifndef _MO_DEBUG_HPP_
#define _MO_DEBUG_HPP_

#include <iostream>
#include <set>
#include <vector>
#include <map>

template <typename T> void __dbg2(T t) { std::cerr << t; }
template <> inline void __dbg2(bool t) { std::cerr << (t ? "true" : "false"); }
template<typename T, typename U> void __dbg2(std::pair<T, U> p) {
	std::cerr << "(";
	__dbg2(p.first);
	std::cerr << ", ";
	__dbg2(p.second);
	std::cerr << ")";
}
template <typename T> void __dbg2(std::vector<T> &v) {
    std::cerr << "[";
    for (int i = 0; i < v.size(); i++) {
		__dbg2(v[i]);
        if (i + 1 < v.size()) {
            std::cerr << ", ";
        }
    }
    std::cerr << "]";
}
template <typename T> void __dbg2(std::set<T> &st) {
    std::cerr << "[";
    int cnt = 0;
    for (auto &item : st) {
        cnt++;
		__dbg2(item);
        if (cnt < st.size()) {
            std::cerr << ", ";
        }
    }
    std::cerr << "]";
}
template<typename K, typename V>
void __dbg2(std::map<K, V> &mp) {
	std::cerr << "[";
	int cnt = 0;
	for (auto &[k, v]: mp) {
		cnt++;
		std::cerr << "{";
		__dbg2(k);
		std::cerr << " -> ";
		__dbg2(v);
		std::cerr << "}";
		if (cnt < mp.size()) {
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
