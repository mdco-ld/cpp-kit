#ifndef _MOG_INTERNAL_PERSISTENT_SEGMENT_TREE_HPP_
#define _MOG_INTERNAL_PERSISTENT_SEGMENT_TREE_HPP_

#include <mog/internal/concepts/monoid.hpp>
#include <vector>

namespace mog::internal {

template <traits::Monoid S> class PersistentSegmentTree {
	using i64 = long long;
	i64 L;
	i64 R;
	struct Node {
		S value;
		Node *left = nullptr;
		Node *right = nullptr;
		int t;
		~Node() {
			if (left != nullptr && left->t == t) {
				delete left;
			}
			if (right != nullptr && right->t == t) {
				delete right;
			}
		}
	};
	std::vector<Node *> root;
	S getValue(Node *node) {
		if (node == nullptr) {
			return S{};
		}
		return node->value;
	}
	void update(Node *node) {
		if (node == nullptr) {
			return;
		}
		node->value = getValue(node->left) + getValue(node->right);
	}

	Node *set(int t, i64 i, S value, i64 tl, i64 tr, Node *node) {
		Node *result = new Node();
		result->t = t;
		if (node != nullptr) {
			result->left = node->left;
			result->right = node->right;
		}
		if (tl == i && tr == i + 1) {
			result->value = value;
			return result;
		}
		i64 tm = tl + (tr - tl) / 2;
		if (i < tm) {
			result->left =
				set(t, i, value, tl, tm, node ? node->left : nullptr);
		} else {
			result->right =
				set(t, i, value, tm, tr, node ? node->right : nullptr);
		}
		update(result);
		return result;
	}

	Node *add(int t, i64 i, S value, i64 tl, i64 tr, Node *node) {
		Node *result = new Node();
		result->t = t;
		if (node != nullptr) {
			result->left = node->left;
			result->right = node->right;
			result->value = node->value;
		}
		if (tl == i && tr == i + 1) {
			result->value += value;
			return result;
		}
		i64 tm = tl + (tr - tl) / 2;
		if (i < tm) {
			result->left =
				add(t, i, value, tl, tm, node ? node->left : nullptr);
		} else {
			result->right =
				add(t, i, value, tm, tr, node ? node->right : nullptr);
		}
		update(result);
		return result;
	}

	S get(i64 i, i64 tl, i64 tr, Node *&node) {
		if (node == nullptr) {
			return S{};
		}
		if (tl == i && tr == i + 1) {
			return node->value;
		}
		i64 tm = tl + (tr - tl) / 2;
		if (i < tm) {
			return get(i, tl, tm, node->left);
		} else {
			return get(i, tm, tr, node->right);
		}
	}

	S sum(i64 l, i64 r, i64 tl, i64 tr, Node *&node) {
		if (node == nullptr) {
			return S{};
		}
		if (tl >= r || tr <= l) {
			return S{};
		}
		if (l <= tl && tr <= r) {
			return node->value;
		}
		i64 tm = tl + (tr - tl) / 2;
		return sum(l, r, tl, tm, node->left) + sum(l, r, tm, tr, node->right);
	}

	void bisect(i64 &result, S acc, auto pred, i64 tl, i64 tr, Node *root) {
		if (root == nullptr) {
			if (pred(acc)) {
				result = tl;
			}
			return;
		}
		i64 tm = tl + (tr - tl) / 2;
		if (pred(acc + getValue(root->left))) {
			result = tm - 1;
			bisect(result, acc, pred, tl, tm, root->left);
		} else {
			bisect(result, acc + getValue(root->left), pred, tm, tr,
				   root->right);
		}
	}

  public:
	PersistentSegmentTree(i64 l, i64 r) : L(l), R(r), root(1, nullptr) {}
	int set(int version, i64 i, S value) {
		root.push_back(set(std::ssize(root), i, value, L, R, root[version]));
		return std::ssize(root) - 1;
	}
	int add(int version, i64 i, S value) {
		root.push_back(add(std::ssize(root), i, value, L, R, root[version]));
		return std::ssize(root) - 1;
	}
	S get(int version, i64 i) { return get(i, L, R, root[version]); }
	S sum(int version, i64 l, i64 r) { return sum(l, r, L, R, root[version]); }
	i64 bisect(int version, auto pred) {
		i64 result = R;
		bisect(result, S{}, pred, L, R, root[version]);
		return result;
	}
	int size() { return std::ssize(root) - 1; }
	~PersistentSegmentTree() {
		while (root.size()) {
			delete root.back();
			root.pop_back();
		}
	}
};

}; // namespace mog::internal

#endif
