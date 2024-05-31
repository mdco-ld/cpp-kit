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

template <typename T = void> struct SegmentTree {
    struct Node {
        int l;
        int r;
        T value;

        Node *left;
        Node *right;

        Node(int L, int R) : Node(L, R, T()) {}

        Node(int L, int R, T val)
            : l(L), r(R), left(nullptr), right(nullptr), value(val) {}

        void add(T val, int i) {
            if (i < l || r < i) {
                return;
            }
            if (l == i && r == i) {
                value = value + val;
                return;
            }
            int mid = l + (r - l) / 2;
            if (l <= i && i <= mid) {
                if (left == nullptr) {
                    left = new Node(l, mid);
                }
                left->add(val, i);
            }
            if (mid < i && i <= r) {
                if (right == nullptr) {
                    right = new Node(mid + 1, r);
                }
                right->add(val, i);
            }
            if (left == nullptr) {
                value = right->value;
                return;
            }
            if (right == nullptr) {
                value = left->value;
                return;
            }
            value = left->value + right->value;
        }

        T query(int L, int R) {
            if (L <= l && r <= R) {
                return value;
            }
            int mid = l + (r - l) / 2;
            if (mid < L) {
                if (right == nullptr) {
                    right = new Node(mid + 1, r);
                }
                return right->query(L, R);
            }
            if (mid + 1 > R) {
                if (left == nullptr) {
                    left = new Node(l, mid);
                }
                return left->query(L, R);
            }
            if (left == nullptr && right == nullptr) {
                return T();
            }
            if (left == nullptr) {
                return right->query(L, R);
            }
            if (right == nullptr) {
                return left->query(L, R);
            }
            return left->query(L, R) + right->query(L, R);
        }
    };

    Node *root;

    SegmentTree() : root(nullptr) {}
    SegmentTree(int l, int r) : SegmentTree() { setup(l, r); }

    void setup(int l, int r) {
        if (root != nullptr) {
            delete root;
        }
        root = new Node(l, r);
    }

    void add(T value, int i) {
        if (root != nullptr) {
            root->add(value, i);
        }
    }

    T query(int L, int R) {
        if (root == nullptr) {
            return T();
        }
        return root->query(L, R);
    }
};

template <> struct SegmentTree<void> {
    struct Node {
        int l;
        int r;
        int value;
        int prop;

        Node *left;
        Node *right;

        Node(int L, int R) : Node(L, R, 0) {}

        Node(int L, int R, int val)
            : l(L), r(R), left(nullptr), right(nullptr), value(val), prop(0) {}

        void propagate() {
            int mid = l + (r - l) / 2;
            if (left == nullptr) {
                left = new Node(l, mid);
            }
            if (right == nullptr) {
                right = new Node(mid + 1, r);
            }

            left->addRange(prop, l, mid);
            right->addRange(prop, mid + 1, r);
            value = left->value + (left->r - left->l + 1) * left->prop +
                    right->value + (right->r - right->l + 1) * right->prop;
            prop = 0;
        }

        void add(int val, int i) {
            if (i < l || r < i) {
                return;
            }
            if (l == i && r == i) {
                value = value + val;
                return;
            }
            if (prop != 0) {
                propagate();
            }
            int mid = l + (r - l) / 2;
            if (l <= i && i <= mid) {
                if (left == nullptr) {
                    left = new Node(l, mid);
                }
                left->add(val, i);
            }
            if (mid < i && i <= r) {
                if (right == nullptr) {
                    right = new Node(mid + 1, r);
                }
                right->add(val, i);
            }
            if (left == nullptr) {
                value = right->value;
                return;
            }
            if (right == nullptr) {
                value = left->value;
                return;
            }
            value = left->value + right->value;
        }

        int query(int L, int R) {
            if (L <= l && r <= R) {
                return value + (r - l + 1) * prop;
            }
            if (prop != 0) {
                propagate();
            }
            int mid = l + (r - l) / 2;
            if (mid < L) {
                if (right == nullptr) {
                    right = new Node(mid + 1, r);
                }
                return right->query(L, R);
            }
            if (R < mid + 1) {
                if (left == nullptr) {
                    left = new Node(l, mid);
                }
                return left->query(L, R);
            }
            if (left == nullptr) {
                left = new Node(l, mid);
            }
            if (right == nullptr) {
                right = new Node(mid + 1, r);
            }
            return left->query(L, R) + right->query(L, R);
        }

        void addRange(int val, int L, int R) {
            if (l > R || L > r) {
                return;
            }
            if (l == r) {
                if (L <= l && r <= R) {
                    value += val;
                }
                return;
            }
            if (L <= l && r <= R) {
                prop += val;
                return;
            }
            int mid = l + (r - l) / 2;
            if (left == nullptr) {
                left = new Node(l, mid);
            }
            if (right == nullptr) {
                right = new Node(mid + 1, r);
            }
            left->addRange(val, L, R);
            right->addRange(val, L, R);
            value = left->value + (left->r - left->l + 1) * left->prop +
                    right->value + (right->r - right->l + 1) * right->prop;
        }
    };

    Node *root;

    SegmentTree() : root(nullptr) {}
    SegmentTree(int l, int r) : SegmentTree() { setup(l, r); }

    void setup(int l, int r) {
        if (root != nullptr) {
            delete root;
        }
        root = new Node(l, r);
    }

    void add(int value, int i) {
        if (root != nullptr) {
            root->add(value, i);
        }
    }

    int query(int L, int R) {
        if (root == nullptr) {
            return 0;
        }
        return root->query(L, R);
    }

    void addRange(int value, int L, int R) {
        if (root != nullptr) {
            root->addRange(value, L, R);
        }
    }
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
