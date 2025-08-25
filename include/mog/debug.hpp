#ifndef _MOG_DEBUG_HPP_
#define _MOG_DEBUG_HPP_

#include <iostream>
#include <map>
#include <mog/fenwick-tree.hpp>
#include <mog/math/matrix.hpp>
#include <mog/modint.hpp>
#include <mog/monoids.hpp>
#include <mog/segtree.hpp>
#include <set>
#include <vector>

template <typename T> void __dbg2(T t) { std::cerr << t; }

template <typename T>
concept Debuggable = requires(T a) {
	{ __dbg2(a) };
} || requires(T a, std::ostream &out) {
	{ out << a } -> std::same_as<std::ostream &>;
};

template <> inline void __dbg2(bool t) { std::cerr << (t ? "true" : "false"); }

template <Debuggable T, Debuggable U> void __dbg2(std::pair<T, U> p) {
	std::cerr << "(";
	__dbg2(p.first);
	std::cerr << ", ";
	__dbg2(p.second);
	std::cerr << ")";
}

template <Debuggable T1, Debuggable T2> void __dbg2(std::tuple<T1, T2> p) {
	std::cerr << "(";
	__dbg2(std::get<0>(p));
	std::cerr << ", ";
	__dbg2(std::get<1>(p));
	std::cerr << ")";
}

template <Debuggable T1, Debuggable T2, Debuggable T3>
void __dbg2(std::tuple<T1, T2, T3> p) {
	std::cerr << "(";
	__dbg2(std::get<0>(p));
	std::cerr << ", ";
	__dbg2(std::get<1>(p));
	std::cerr << ", ";
	__dbg2(std::get<2>(p));
	std::cerr << ")";
}

template <Debuggable T1, Debuggable T2, Debuggable T3, Debuggable T4>
void __dbg2(std::tuple<T1, T2, T3, T4> p) {
	std::cerr << "(";
	__dbg2(std::get<0>(p));
	std::cerr << ", ";
	__dbg2(std::get<1>(p));
	std::cerr << ", ";
	__dbg2(std::get<2>(p));
	std::cerr << ", ";
	__dbg2(std::get<3>(p));
	std::cerr << ")";
}

template <Debuggable T> void __dbg2(const std::set<T> &st) {
	std::cerr << "[";
	int cnt = 0;
	for (const auto &item : st) {
		cnt++;
		__dbg2(item);
		if (cnt < st.size()) {
			std::cerr << ", ";
		}
	}
	std::cerr << "]";
}
template <Debuggable T> void __dbg2(std::vector<T> &v) {
	std::cerr << "[";
	for (int i = 0; i < v.size(); i++) {
		__dbg2(v[i]);
		if (i + 1 < v.size()) {
			std::cerr << ", ";
		}
	}
	std::cerr << "]";
}

template <Debuggable K, Debuggable V> void __dbg2(std::map<K, V> &mp) {
	std::cerr << "[";
	int cnt = 0;
	for (auto &[k, v] : mp) {
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

template <> inline void __dbg2(mog::Int998244353 x) {
	std::cerr << x.toInt() << 'm';
}

template <> inline void __dbg2(mog::Int1e9p7 x) {
	std::cerr << x.toInt() << 'm';
}

template <Debuggable T> void __dbg2(mog::MaxMonoid<T> x) { __dbg2(x.value); }

template <Debuggable T> void __dbg2(mog::MinMonoid<T> x) { __dbg2(x.value); }

template <Debuggable T> void __dbg2(mog::ReverseMonoid<T> x) {
	__dbg2(x.value);
}

template <Debuggable T> void __dbg2(mog::ProductMonoid<T> x) {
	__dbg2(x.value);
}

template <Debuggable T> void __dbg2(mog::FenwickTree<T> &fw) {
	std::cerr << "Fenwick{";
	for (int i = 1; i <= fw.size(); i++) {
		if (i > 1) {
			std::cerr << ", ";
		}
		__dbg2(fw[i]);
	}
	std::cerr << "}";
}

template <Debuggable T> void __dbg2(mog::Segtree<T> &seg) {
	std::cerr << "Segtree{";
	for (int i = 0; i < seg.size(); i++) {
		if (i > 0) {
			std::cerr << ", ";
		}
		__dbg2(seg.get(i));
	}
	std::cerr << "}";
}

template <Debuggable T, int N, int M> void __dbg2(mog::MatrixN<T, N, M> mat) {
	std::cerr << "Mat{";
	for (int i = 0; i < N; i++) {
		if (i > 0) {
			std::cerr << ", ";
		}
		std::cerr << '[';
		for (int j = 0; j < M; j++) {
			if (j > 0) {
				std::cerr << ", ";
			}
			__dbg2(mat[i][j]);
		}
		std::cerr << ']';
	}
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

#define dbgif(cond, ...)                                                       \
	do {                                                                       \
		if (cond)                                                              \
			dbg(__VA_ARGS__);                                                  \
	} while (0)

#endif
