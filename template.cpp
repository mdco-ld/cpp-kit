#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define int ll

void __dbg() { cerr << endl; }
template <typename T> void __dbg(T t) { cerr << t << endl; }
template <typename T, typename... TRest> void __dbg(T first, TRest... rest) {
    cerr << first << ", ";
    __dbg(rest...);
}
#define dbg(...)                                                               \
    do {                                                                       \
        cerr << "DBG> " << "(" << #__VA_ARGS__ << ") = ";                      \
        __dbg(__VA_ARGS__);                                                    \
    } while (0)

#define unreachable                                                            \
    do {                                                                       \
        assert(false);                                                         \
    } while (0)

template <typename T> T maxx(T t) { return t; }
template <typename T, typename... TRest> T maxx(T first, TRest... rest) {
    return max<T>(first, maxx(rest...));
}
template <typename T> T minn(T t) { return t; }
template <typename T, typename... TRest> T minn(T first, TRest... rest) {
    return min<T>(first, minn(rest...));
}

template <size_t maxn, bool digraph = false> struct Graph {
    vector<int> edges[maxn];
    int n;
    Graph() { n = 0; };
    void clear() {
        for (int i = 0; i <= n; i++) {
            edges[i].clear();
        }
		n = 0;
    }
    void edge(int a, int b) {
        n = maxx(n, a, b);
        if constexpr (digraph) {
            edges[a].push_back(b);
        } else {
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }
    vector<int> &operator[](int a) { return edges[a]; }
};

template <size_t maxn, bool digraph = false> struct WGraph {
	struct Edge {
		int v;
		int w;
		bool operator<(const Edge &other) const {
			return toPair() < other.toPair();
		}
		pair<int, int> toPair() {
			return {w, v};
		};
	};
    vector<Edge> edges[maxn];
    int n;
    WGraph() { n = 0; };
    void clear() {
        for (int i = 0; i <= n; i++) {
            edges[i].clear();
        }
		n = 0;
    }
    void edge(int a, int b, int w) {
        n = maxx(n, a, b);
        if constexpr (digraph) {
            edges[a].push_back({b, w});
        } else {
            edges[a].push_back({b, w});
            edges[b].push_back({a, w});
        }
    }
    vector<Edge> &operator[](int a) { return edges[a]; }
};

const int MOD = 1e9 + 7;

mt19937 rng(random_device{}());

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
    }
    return 0;
}
