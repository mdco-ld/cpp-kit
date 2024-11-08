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

const int MOD = 1e9 + 7;
const int N = 4e5 + 5;

mt19937 rng(random_device{}());
int n, m, k, q;
int v[N];
vector<int> edges[N];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
    }
    return 0;
}
