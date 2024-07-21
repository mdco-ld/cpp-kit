#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define int ll

#define let auto
#define fn [&]
#define fnc [=]
#define MOD (1000000007ll)

#define YES                                                                    \
    do {                                                                       \
        cout << "Yes\n";                                                       \
        return;                                                                \
    } while (0)
#define NO                                                                     \
    do {                                                                       \
        cout << "No\n";                                                        \
        return;                                                                \
    } while (0)

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

template <typename T> void readList(vector<T> &v) {
    for (let &t : v) {
        cin >> t;
    }
}

template <typename T> void readList(vector<T> &v, int &n) {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
}

template <typename T> void printList(vector<T> &v, const char *delim = " ") {
    for (let x : v) {
        cout << x << delim;
    }
    cout << endl;
}

template <typename T, typename U>
ostream &operator<<(ostream &out, pair<T, U> p) {
    return out << p.first << " " << p.second;
}

namespace geo {

template <typename T = int> struct point {
    T x;
    T y;

    point() : x(0), y(0) {}
    point(T x, T y) : x(x), y(y) {}
    point(const point &other) : x(other.x), y(other.y) {}
    point operator-() { return point(-x, -y); }
    point operator+(const point &other) {
        return point(other.x + x, other.y + y);
    }
    point operator-(const point &other) {
        return point(x - other.x, y - other.y);
    }
    point operator*(T val) { return point(x * val, y * val); }
    T operator*(point other) { return x * other.x + y * other.y; }
};

template <typename T> T shoelace(point<T> p1, point<T> p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

template <typename T = int> T area(point<T> p1, point<T> p2, point<T> p3) {
    return shoelace(p1, p2) + shoelace(p2, p3) + shoelace(p3, p1);
}

template <typename T = int>
bool intersects(point<T> p1, point<T> p2, point<T> p3, point<T> p4) {
    if (area(p1, p2, p3) == 0 && area(p1, p2, p4) == 0) {
        let inter = fn(int a, int b, int c, int d) {
            if (a > b) {
                swap(a, b);
            }
            if (c > d) {
                swap(c, d);
            }
            return max(a, c) <= min(b, d);
        };
        return inter(p1.x, p2.x, p3.x, p4.x) && inter(p1.y, p2.y, p3.y, p4.y);
    }
    let sgn = [](int x) {
        if (x == 0) {
            return 0;
        }
        if (x < 0) {
            return -1;
        }
        return 1;
    };
    return sgn(area(p1, p2, p3)) != sgn(area(p1, p2, p4)) &&
           sgn(area(p3, p4, p1)) != sgn(area(p3, p4, p2));
}

using pointf = point<double>;

}; // namespace geo

struct DSU {
    vector<int> parent;
    vector<int> cnt;

    DSU() {}

    void make_set(int x) {
        if (parent.size() <= x) {
            parent.resize(x + 1);
        }
        if (cnt.size() <= x) {
            cnt.resize(x + 1);
        }
        parent[x] = x;
        cnt[x] = 1;
    }

    int find(int x) {
        if (x >= parent.size()) {
            make_set(x);
            return x;
        }
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void join(int x, int y) {
        x = find(x);
        y = find(y);

        if (cnt[x] < cnt[y]) {
            swap(x, y);
        }
        parent[y] = x;
        cnt[x] += cnt[y];
    }

    bool same(int x, int y) {
        x = find(x);
        y = find(y);
        return x == y;
    }
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

        void update(T val, int i) {
            if (i < l || r < i) {
                return;
            }
            if (l == i && r == i) {
                value = val;
                return;
            }
            int mid = l + (r - l) / 2;
            if (l <= i && i <= r) {
                if (left == nullptr) {
                    left = new Node(l, mid);
                }
                left->update(val, i);
            }
            if (mid < i && i <= r) {
                if (right == nullptr) {
                    right = new Node(mid + 1, r);
                }
                right->update(val, i);
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
            if (R < L) {
                return T();
            }
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

    void update(T value, int i) {
        if (root != nullptr) {
            root->update(value, i);
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

    void update(int value, int i) {
        int val = query(i, i);
        add(-val, i);
        add(value, i);
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

constexpr int phi_ct(int n) {
    if (n == MOD) {
        return n - 1;
    }
    if (n == MOD - 1) {
        return (n - 1) / 2 - 1;
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            int c = 0;
            while (n % i == 0) {
                n /= i;
                c++;
            }
            result *= i - 1;
            for (int i = 1; i < c; i++) {
                result *= i;
            }
        }
    }
    return result;
}

struct Sieve {
    vector<int32_t> lp;
    vector<int32_t> pr;

    Sieve() {}

    Sieve(int n) { setup(n); }

    void setup(int n) {
        lp.resize(n + 1);
        pr.clear();
        for (int i = 2; i <= n; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (int j = 0; i * pr[j] <= n; j++) {
                lp[i * pr[j]] = pr[j];
                if (pr[j] == lp[i]) {
                    break;
                }
            }
        }
    }

    inline bool is_prime(int p) { return lp[p] == p; }

    inline int prime(int idx) { return pr[idx]; }
};

struct intmax {
    int value;

    intmax() : value(numeric_limits<int>::min()) {}
    intmax(int v) : value(v) {}

    intmax operator+(intmax other) { return intmax(max(value, other.value)); }
    operator int() { return value; }
};

struct intmin {
    int value;

    intmin() : value(numeric_limits<int>::max()) {}
    intmin(int v) : value(v) {}

    intmin operator+(intmin other) { return intmin(min(value, other.value)); }
    operator int() { return value; }
};

template <int mod> struct intmod {
    static constexpr int mod_phi = phi_ct(mod);
    int value;
    constexpr intmod() : value(0) {}
    constexpr intmod(int x) {
        value = x % mod;
        if (value < 0) {
            value += mod;
        }
    }
    constexpr operator int() { return value; }
    constexpr intmod pow(int e) {
        intmod result = 1;
        intmod base = value;
        if (e < 0) {
            e = (e % mod_phi) + mod_phi;
        }
        while (e) {
            if (e & 1) {
                result *= base;
            }
            base *= base;
            e /= 2;
        }
        return result;
    }
    static constexpr intmod inverse(int x) {
        return x <= 1 ? x : mod - (int)(mod / x) * inverse(mod % x) % mod;
    }
    constexpr intmod inverse() { return inverse(value); }
    constexpr intmod operator+(intmod other) {
        return intmod(value + other.value);
    }
    constexpr intmod operator-(intmod other) {
        return intmod(value - other.value);
    }
    constexpr intmod operator*(intmod other) {
        return intmod(value * other.value);
    }
    constexpr intmod operator/(intmod other) { return *this * other.inverse(); }
    constexpr intmod operator+=(intmod other) {
        value = (value + other.value) % mod;
        return *this;
    }
    constexpr intmod operator-=(intmod other) {
        value = (value - other.value) % mod;
        return *this;
    }
    constexpr intmod operator*=(intmod other) {
        value = (value * other.value) % mod;
        return *this;
    }
    constexpr intmod operator++() {
        value = (value + 1) % mod;
        return *this;
    }
    constexpr intmod operator++(int32_t) {
        value = (value + 1) % mod;
        return *this - 1;
    }
    constexpr intmod operator--() {
        value = (value - 1 + mod) % mod;
        return *this;
    }
    constexpr intmod operator--(int32_t) {
        value = (value - 1 + mod) % mod;
        return *this + 1;
    }
};

template <int mod> struct Combinatorics {

    vector<intmod<mod>> fact_cache = {1};

    intmod<mod> fact(int n) {
        if (n == 0) {
            return 1;
        }
        if (fact_cache.size() > n) {
            return fact_cache[n];
        }
        intmod<mod> prev = fact(n - 1);
        fact_cache.push_back(prev * intmod<mod>(n));
        return fact_cache[n];
    }

    intmod<mod> choose(int n, int k) {
        if (k > n) {
            return 0;
        }
        return fact(n) / (fact(n - k) * fact(k));
    }
};

static Combinatorics<MOD> combo;

using pii = pair<int, int>;
using intm = intmod<MOD>;

int bs_first(int start, int end, function<bool(int)> f) {
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (f(mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return ans;
}

int bs_last(int start, int end, function<bool(int)> f) {
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (f(mid)) {
            ans = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return ans;
}

int n;
vector<int> v;

void solve() {}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
