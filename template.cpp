#include <bits/stdc++.h>

using namespace std;

#if 0
#define _USE_T
#endif

#if defined(_mdco_local_)
#define print(e) cerr << e << endl
#else
#define print(e)
#endif

using ll = long long;

#define let auto

#define int ll

#define fn(...) [&](__VA_ARGS__)

template <typename T = int> struct Point {
    T x;
    T y;

    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    Point(const Point &other) : x(other.x), y(other.y) {}
    Point operator-() { return Point(-x, -y); }
    Point operator+(const Point &other) {
        return Point(other.x + x, other.y + y);
    }
    Point operator-(const Point &other) {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(T val) { return Point(x * val, y * val); }
};

// Idempotent range queries
template <typename T> struct IRQ {
    vector<vector<T>> lkup;

    IRQ(const vector<T> &vec) {
        lkup.resize(vec.size());
        for (int i = 0; i < vec.size(); i++) {
            lkup[i].push_back(vec[i]);
        }
        for (int size = 2; size < vec.size(); size *= 2) {
            for (int i = 0; i + size <= vec.size(); i++) {
                lkup[i].push_back(lkup[i].back() + lkup[i + size / 2].back());
            }
        }
    }

    T query(int l, int r) {
        if (l == r) {
            return lkup[l][0];
        }
        int pow = 1;
        while ((2 << pow) < r - l + 1) {
            pow++;
        }
        int size = 1 << pow;
        return lkup[l][pow] + lkup[r - size + 1][pow];
    }
};

struct DSUBase {
  private:
    vector<int> parent;
    vector<int> size;

  public:
    DSUBase() {}
    DSUBase(int n) {
        size.assign(n, 1);
        parent.resize(n);
    }

    void make_set(int x) {
        if (x >= parent.size()) {
            parent.resize(x + 1);
        }
        if (x >= size.size()) {
            size.resize(x + 1);
        }
        parent[x] = x;
    }

    int find(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        parent[y] = x;
        size[x] += size[y];
    }

    bool same(int x, int y) { return find(x) == find(y); }
};

template <typename T = void> struct DSU {
  private:
    DSUBase base;

    map<T, int> id;
    map<int, T> val;
    int next_id;

  public:
    DSU() { next_id = 0; }

    void make_set(T x) {
        if (id.count(x)) {
            return;
        }
        id.insert({x, next_id});
        val.insert({next_id, x});
        base.make_set(next_id);
        next_id++;
    }

    T find(T v) {
        int x = id[v];
        int p = base.find(x);
        return val[p];
    }

    void merge(T x, T y) {
        int x_id = id[x];
        int y_id = id[y];
        base.merge(x_id, y_id);
    }

    bool same(T x, T y) {
        int x_id = id[x];
        int y_id = id[y];
        return base.same(x_id, y_id);
    }
};

template <> struct DSU<void> : public DSUBase {
    DSU() : DSUBase() {}
    DSU(int n) : DSUBase(n) {}
};

/*
 * Solution Code
 */

void solve() {
	// Solution
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#if defined(_USE_T)
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
#else
    solve();
#endif
    return 0;
}
