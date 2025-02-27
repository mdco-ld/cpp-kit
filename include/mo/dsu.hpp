#ifndef _MO_DSU_HPP_
#define _MO_DSU_HPP_

#include <numeric>
#include <stack>
#include <vector>

namespace mo {

template <void (*onJoin)(int, int) = nullptr> class DSU {
  private:
    std::vector<int> parent;
    std::vector<int> cnt;
    int n;

  public:
    DSU(int n) : n(n), parent(n + 1), cnt(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    inline int getCnt(int x) { return cnt[x]; }

    int root(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = root(parent[x]);
    }

    bool join(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return false;
        }
        if (cnt[x] < cnt[y]) {
            std::swap(x, y);
        }
        onJoin(x, y);
        cnt[x] += cnt[y];
        parent[y] = x;
        return true;
    }
};

template <> class DSU<nullptr> {
  private:
    std::vector<int> parent;
    std::vector<int> cnt;
    int n;

  public:
    DSU(int n) : n(n), parent(n + 1), cnt(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    inline int getCnt(int x) { return cnt[x]; }

    int root(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = root(parent[x]);
    }

    bool join(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return false;
        }
        if (cnt[x] < cnt[y]) {
            std::swap(x, y);
        }
        cnt[x] += cnt[y];
        parent[y] = x;
        return true;
    }
};

template<typename T>
class DSURollback {
  private:
    struct Operation {
        T x;
        T y;
        int depthX;
    };
    std::vector<T> parent;
    std::vector<int> depth;
    std::stack<Operation> changes;
    int n;

  public:
    DSURollback(int n) : n(n), parent(n + 1), depth(n + 1, T{}) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    T root(T x) {
        if (parent[x] == x) {
            return x;
        }
        return root(parent[x]);
    }

	bool isConnected(T x, T y) {
		return root(x) == root(y);
	}

    bool join(T x, T y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return false;
        }
        if (depth[x] < depth[y]) {
            std::swap(x, y);
        }
        Operation change;
        change.x = x;
        change.y = y;
        change.depthX = depth[x];
        changes.push(change);
        parent[y] = x;
        if (depth[x] == depth[y]) {
            depth[x]++;
        }
        return true;
    }

    void rollback() {
        if (changes.empty()) {
            return;
        }
        Operation change = changes.top();
        changes.pop();
        depth[change.x] = change.depthX;
        parent[change.y] = change.y;
    }
};

class DSU2D {
  private:
    std::vector<std::vector<std::pair<int, int>>> parent;
    std::vector<std::vector<int>> cnt;
    int n;
    int m;

  public:
    DSU2D(int n, int m)
        : n(n), m(m), parent(n + 1, std::vector<std::pair<int, int>>(m + 1)),
          cnt(n + 1, std::vector<int>(m + 1, 1)) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                parent[i][j] = {i, j};
            }
        }
    }

    std::pair<int, int> root(std::pair<int, int> x) {
        if (parent[x.first][x.second] == x) {
            return x;
        }
        return parent[x.first][x.second] = root(parent[x.first][x.second]);
    }

    bool join(std::pair<int, int> x, std::pair<int, int> y) {
        x = root(x);
        y = root(y);
        if (x == y) {
            return false;
        }
        if (cnt[x.first][x.second] < cnt[y.first][y.second]) {
            std::swap(x, y);
        }
        cnt[x.first][x.second] += cnt[y.first][y.second];
        parent[y.first][y.second] = x;
        return true;
    }
};

}; // namespace mo

#endif
