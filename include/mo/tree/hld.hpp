#ifndef _MO_TREE_HLD_HPP_
#define _MO_TREE_HLD_HPP_

#include <mo/lazy-segtree.hpp>
#include <mo/segtree.hpp>
#include <mo/tree/tree.hpp>

namespace mo {

namespace tree {

template <class T, T (*op)(T, T), T (*e)(), bool oneBased = true> class HLD {
  public:
    using Segtree = SegmentTree<T, op, e>;

    HLD(Tree<int, oneBased> &t) : HLD(t, oneBased) {}

    HLD(Tree<int, oneBased> &t, int root)
        : n(t.size()), root(root), tin(t.size() + oneBased),
          tout(t.size() + oneBased), nxt(t.size() + oneBased, -1),
          head(t.size() + oneBased), cnt(t.size() + oneBased, 1),
          par(t.size() + oneBased), depth(t.size() + oneBased), t(t) {
        st.build(n);
        getCnt(root);
        head[root] = root;
        prepare(root);
    }

    void update(int v, T value) { st.update(tin[v], value); }

    void add(int v, T value) { st.add(tin[v], value); }

    T querySubtree(int v) { return st.query(tin[v], tout[v]); }

    T query(int v, int u) {
        T ans = e();
        while (head[v] != head[u]) {
            if (depth[head[v]] < depth[head[u]]) {
                ans = op(ans, st.query(tin[head[u]], tin[u] + 1));
                u = par[head[u]];
            } else {
                ans = op(ans, st.query(tin[head[v]], tin[v] + 1));
                v = par[head[v]];
            }
        }
        if (u == v) {
            ans = op(ans, st.get(tin[v]));
            return ans;
        }
        if (depth[v] > depth[u]) {
            ans = op(ans, st.query(tin[u], tin[v] + 1));
        } else {
            ans = op(ans, st.query(tin[v], tin[u] + 1));
        }
        return ans;
    }

    inline int getRoot() { return root; }

  private:
    int n;
    int root;
    Segtree st;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> nxt;
    std::vector<int> head;
    std::vector<int> cnt;
    std::vector<int> par;
    std::vector<int> depth;
    Tree<int, oneBased> &t;
    int tm = 0;

    void getCnt(int v, int p = -1) {
        par[v] = p == -1 ? v : p;
        for (int u : t[v]) {
            if (u == p) {
                continue;
            }
            depth[u] = depth[v] + 1;
            getCnt(u, v);
            cnt[v] += cnt[u];
            if (nxt[v] == -1 || cnt[u] > cnt[nxt[v]]) {
                nxt[v] = u;
            }
        }
    }

    void prepare(int v) {
        tin[v] = tm++;
        if (nxt[v] != -1) {
            head[nxt[v]] = head[v];
            prepare(nxt[v]);
        }
        for (int u : t[v]) {
            if (u == par[v] || u == nxt[v]) {
                continue;
            }
            head[u] = u;
            prepare(u);
        }
        tout[v] = tm;
    }
};

template <class T, T (*op)(T, T), T (*e)(), class U, T (*mapping)(U, T),
          U (*compose)(U, U), U (*id)(), bool oneBased = true>
class LazyHLD {
  public:
    using Segtree = LazySegtree<T, op, e, U, mapping, compose, id>;

    LazyHLD(Tree<int, oneBased> &t) : LazyHLD(t, oneBased) {}

    LazyHLD(Tree<int, oneBased> &t, int root)
        : n(t.size()), root(root), tin(t.size() + oneBased),
          tout(t.size() + oneBased), nxt(t.size() + oneBased, -1),
          head(t.size() + oneBased), cnt(t.size() + oneBased, 1),
          par(t.size() + oneBased), depth(t.size() + oneBased), t(t) {
        st.build(n);
        getCnt(root);
        head[root] = root;
        prepare(root);
    }

    void update(int v, T value) { st.update(tin[v], value); }

    void applySubtree(int v, U upd) { st.apply(tin[v], tout[v], upd); }

    void apply(int v, int u, U upd) {
        while (head[v] != head[u]) {
            if (depth[head[v]] < depth[head[u]]) {
                st.apply(tin[head[u]], tin[u] + 1, upd);
                u = par[head[u]];
            } else {
                st.apply(tin[head[v]], tin[v] + 1, upd);
                v = par[head[v]];
            }
        }
        if (u == v) {
            st.apply(tin[v], tin[v], upd);
        }
        if (depth[v] > depth[u]) {
            st.apply(tin[u], tin[v], upd);
        } else {
            st.apply(tin[v], tin[u], upd);
        }
    }

    T querySubtree(int v) { return st.query(tin[v], tout[v]); }

    T query(int v, int u) {
        T ans = e();
        while (head[v] != head[u]) {
            if (depth[head[v]] < depth[head[u]]) {
                ans = op(ans, st.query(tin[head[u]], tin[u] + 1));
                u = par[head[u]];
            } else {
                ans = op(ans, st.query(tin[head[v]], tin[v] + 1));
                v = par[head[v]];
            }
        }
        if (u == v) {
            ans = op(ans, st.get(tin[v]));
            return ans;
        }
        if (depth[v] > depth[u]) {
            ans = op(ans, st.query(tin[u], tin[v] + 1));
        } else {
            ans = op(ans, st.query(tin[v], tin[u] + 1));
        }
        return ans;
    }

    inline int getRoot() { return root; }

  private:
    int n;
    int root;
    Segtree st;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> nxt;
    std::vector<int> head;
    std::vector<int> cnt;
    std::vector<int> par;
    std::vector<int> depth;
    Tree<int, oneBased> &t;
    int tm = 0;

    void getCnt(int v, int p = -1) {
        par[v] = p == -1 ? v : p;
        for (int u : t[v]) {
            if (u == p) {
                continue;
            }
            depth[u] = depth[v] + 1;
            getCnt(u, v);
            cnt[v] += cnt[u];
            if (nxt[v] == -1 || cnt[u] > cnt[nxt[v]]) {
                nxt[v] = u;
            }
        }
    }

    void prepare(int v) {
        tin[v] = tm++;
        if (nxt[v] != -1) {
            head[nxt[v]] = head[v];
            prepare(nxt[v]);
        }
        for (int u : t[v]) {
            if (u == par[v] || u == nxt[v]) {
                continue;
            }
            head[u] = u;
            prepare(u);
        }
        tout[v] = tm;
    }
};

}; // namespace tree

}; // namespace mo

#endif
