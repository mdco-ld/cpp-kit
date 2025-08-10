#ifndef _MO_DYNAMIC_SEGTREE_HPP_
#define _MO_DYNAMIC_SEGTREE_HPP_

#include <mo/utils.hpp>

#include <vector>

namespace mo {

template <typename T, T (*op)(T, T), T (*e)()> class DynSegtree {
  public:
    void build(Interval interval) {
        t.clear();
        root = makeNode(interval);
    }

    T query(Interval interval) { return query(interval, root); }

    void update(int64_t position, T value) { update(position, value, root); }

    void add(int64_t position, T value) { add(position, value, root); }

  private:
    struct Node {
        Interval interval;
        T sum;
        int left;
        int right;
    };

    int root = -1;
    std::vector<Node> t;

    T query(Interval interval, int node) {
        if (node == -1) {
            return e();
        }
		if (interval.isDisjoint(t[node].interval)) {
			return e();
		}
        if (interval.contains(t[node].interval)) {
            return t[node].sum;
        }
        return op(query(interval, t[node].left), query(interval, t[node].right));
    }

    void update(int64_t position, T value, int node) {
        if (!t[node].interval.contains(position)) {
            return;
        }
        if (t[node].interval.size() == 1) {
            t[node].sum = value;
            return;
        }
        if (t[node].interval.left().contains(position)) {
            if (t[node].left == -1) {
                t[node].left = makeNode(t[node].interval.left());
            }
            update(position, value, t[node].left);
        }
        if (t[node].interval.right().contains(position)) {
            if (t[node].right == -1) {
                t[node].right = makeNode(t[node].interval.right());
            }
            update(position, value, t[node].right);
        }
		pull(node);
    }

    void add(int64_t position, T value, int node) {
        if (!t[node].interval.contains(position)) {
            return;
        }
        if (t[node].interval.size() == 1) {
            t[node].sum = op(value, t[node].sum);
            return;
        }
        if (t[node].interval.left().contains(position)) {
            if (t[node].left == -1) {
                t[node].left = makeNode(t[node].interval.left());
            }
            update(position, value, t[node].left);
        }
        if (t[node].interval.right().contains(position)) {
            if (t[node].right == -1) {
                t[node].right = makeNode(t[node].interval.right());
            }
            update(position, value, t[node].right);
        }
		pull(node);
    }

    void pull(int node) {
        if (t[node].left == -1 && t[node].right == -1) {
            return;
        }
        if (t[node].left == -1) {
            t[node].sum = t[t[node].right].sum;
            return;
        }
        if (t[node].right == -1) {
            t[node].sum = t[t[node].left].sum;
            return;
        }
        t[node].sum = op(t[t[node].left].sum, t[t[node].right].sum);
    }

    int makeNode(Interval interval) {
        int ret = t.size();
        t.emplace_back(interval, e(), -1, -1);
		return ret;
    }
};

}; // namespace mo

#endif
