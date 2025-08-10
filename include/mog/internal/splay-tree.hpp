#ifndef _MOG_INTERNAL_SPLAY_TREE_HPP_
#define _MOG_INTERNAL_SPLAY_TREE_HPP_

#include <mog/internal/concepts/monoid.hpp>
#include <utility>
#include <vector>

namespace mog::internal {

template <class T> class SplayTree {
  public:
	SplayTree() : root(nullptr) {}
	~SplayTree() { delete root; }

	void insertBack(T value) {
		Node *node = new Node(value);
		if (!root) {
			root = node;
			return;
		}
		Node *par = find(size() - 1);
		par->child[1] = node;
		node->parent = par;
		splay(node);
	}

	void insert(T value, int position) {
		Node *node = new Node(value);
		if (position == 0) {
			Node *par = find(0);
			par->child[0] = node;
			node->parent = par;
			splay(node);
			return;
		}
		Node *par = find(position - 1);
		if (!par->child[1]) {
			par->child[1] = node;
			splay(node);
			return;
		}
		par = par->child[1];
		while (par->child[0]) {
			par = par->child[0];
		}
		par->child[0] = node;
		node->parent = par;
	}

	template <typename... Ts> void emplaceBack(Ts... args) {
		// TODO: Make inline constructor for Node.
		Node *node = new Node(T(std::forward(args...)));
		if (!root) {
			root = node;
			return;
		}
		Node *par = find(size() - 1);
		par->child[1] = node;
		node->parent = par;
		splay(node);
	}

	int size() { return Node::getCount(root); }

	void remove(int idx) { extractInterval(idx, idx); }

	/**
	 * Extracts the interval [l, r] into another splay tree
	 */
	SplayTree extractInterval(int l, int r) {
		auto interval = splayInterval(l, r);
		SplayTree ret;
		if (interval->parent) {
			int dir = Node::dir(interval);
			interval->parent[dir] = nullptr;
			interval->parent = nullptr;
		}
		ret.root = interval;
		return ret;
	}

	void insertTree(SplayTree &st, int position) {
		auto node = find(position);
		if (node->child[1] == nullptr) {
			node->child[1] = st.root;
			st.root->parent = node;
			splay(st.root);
			st.root = nullptr;
			return;
		}
		node = node->child[1];
		while (node->chid[0]) {
			node = node->child[0];
		}
		node->child[0] = st.root;
		st.root->parent = node;
		splay(st.root);
		st.root = nullptr;
	}

	T &operator[](int idx) {
		auto node = find(idx);
		return node->value;
	}

	std::vector<T> values() const {
		std::vector<T> vals;
		inOrder(vals, root);
		return vals;
	}

	void clear() { delete root; }

  private:
	struct Node {
		T value;
		Node *child[2];
		Node *parent;
		int count;
		Node(T value) : value(value), parent(nullptr), count(1) {
			child[0] = child[1] = nullptr;
		}
		static int getCount(Node *node) {
			if (!node) {
				return 0;
			}
			return node->count;
		}
		static void update(Node *node) {
			if (!node) {
				return;
			}
			node->count =
				1 + getCount(node->child[0]) + getCount(node->child[1]);
		}
		static int dir(Node *node) {
			return node->parent && node->parent->child[1] == node;
		}
		~Node() {
			for (int i : {0, 1}) {
				if (child[i]) {
					delete child[i];
				}
			}
		}
	};

	Node *root;

	void inOrder(std::vector<T> &vals, Node *node) const {
		if (!node) {
			return;
		}
		inOrder(node->child[0]);
		vals.push_back(node->value);
		inOrder(node->child[1]);
	}

	void rotate(Node *node) {
		if (!node->parent) {
			return;
		}
		auto &parent = node->parent;
		int dir = Node::dir(node);
		parent->child[dir] = node->child[!dir];
		node->parent = parent->parent;
		node->child[!dir] = parent;
		Node::update(parent);
		Node::update(node);
	}

	void splay(Node *node, Node *parent = nullptr) {
		while (node->parent != parent) {
			if (node->parent->parent == parent) {
				rotate(node);
				return;
			}
			if (Node::dir(node) == Node::dir(node->parent)) {
				rotate(node->parent);
				rotate(node);
			} else {
				rotate(node);
				rotate(node);
			}
		}
	}

	Node *find(int i) {
		Node *current = root;
		while (current) {
			if (i < Node::getCount(current->child[0])) {
				current = current->child[0];
				continue;
			}
			i -= Node::getCount(current->child[0]);
			if (i == 0) {
				splay(current);
				return current;
			}
			i--;
			current = current->child[1];
		}
		return nullptr;
	}

	/**
	 * Splays the interval [l, r]
	 */
	Node *splayInterval(int l, int r) {
		int n = size();
		if (l == 0 && r + 1 == n) {
			return root;
		}
		if (l == 0) {
			auto R = find(r + 1);
			return R->child[0];
		}
		if (r + 1 == n) {
			auto L = find(l - 1);
			return L->child[1];
		}
		auto L = find(l - 1);
		auto R = find(r + 1);
		splay(L, R);
		return L->child[1];
	}
};

template <mog::internal::traits::Monoid S> class SplayTreeMonoid {
  public:
	SplayTreeMonoid() : root(nullptr) {}
	~SplayTreeMonoid() { delete root; }

	void insertBack(S value) {
		Node *node = new Node(value);
		if (!root) {
			root = node;
			return;
		}
		Node *par = find(size() - 1);
		par->child[1] = node;
		node->parent = par;
		splay(node);
	}

	void insert(S value, int position) {
		Node *node = new Node(value);
		if (position == 0) {
			Node *par = find(0);
			par->child[0] = node;
			node->parent = par;
			splay(node);
			return;
		}
		Node *par = find(position - 1);
		if (!par->child[1]) {
			par->child[1] = node;
			splay(node);
			return;
		}
		par = par->child[1];
		while (par->child[0]) {
			par = par->child[0];
		}
		par->child[0] = node;
		node->parent = par;
	}

	template <typename... Ts> void emplaceBack(Ts... args) {
		// TODO: Make inline constructor for Node.
		Node *node = new Node(S(std::forward(args...)));
		if (!root) {
			root = node;
			return;
		}
		Node *par = find(size() - 1);
		par->child[1] = node;
		node->parent = par;
		splay(node);
	}

	int size() { return Node::getCount(root); }

	/**
	 * Extracts the interval [l, r] into another splay tree
	 */
	SplayTreeMonoid extractInterval(int l, int r) {
		auto interval = splayInterval(l, r);
		SplayTreeMonoid ret;
		if (interval->parent) {
			int dir = Node::dir(interval);
			interval->parent[dir] = nullptr;
			interval->parent = nullptr;
		}
		ret.root = interval;
		return ret;
	}

	void insertTree(SplayTreeMonoid &st, int position) {
		auto node = find(position);
		if (node->child[1] == nullptr) {
			node->child[1] = st.root;
			st.root->parent = node;
			splay(st.root);
			st.root = nullptr;
			return;
		}
		node = node->child[1];
		while (node->chid[0]) {
			node = node->child[0];
		}
		node->child[0] = st.root;
		st.root->parent = node;
		splay(st.root);
		st.root = nullptr;
	}

	S operator[](int idx) {
		auto node = find(idx);
		return node->value;
	}

	void update(int idx, S value) {
		auto node = find(idx);
		node->value = value;
		Node::update(node);
	}

	std::vector<S> values() const {
		std::vector<S> vals;
		inOrder(vals, root);
		return vals;
	}

	void clear() { delete root; }

  private:
	struct Node {
		S value;
		S sum;
		Node *child[2];
		Node *parent;
		int count;
		Node(S value) : value(value), sum(value), parent(nullptr), count(1) {
			child[0] = child[1] = nullptr;
		}
		static int getCount(Node *node) {
			if (!node) {
				return 0;
			}
			return node->count;
		}
		static S getSum(Node *node) {
			if (!node) {
				return S{};
			}
			return node->sum;
		}
		static void update(Node *node) {
			if (!node) {
				return;
			}
			node->count =
				1 + getCount(node->child[0]) + getCount(node->child[1]);
			node->sum =
				getSum(node->child[0]) + node->value + getSum(node->child[1]);
		}
		static int dir(Node *node) {
			return node->parent && node->parent->child[1] == node;
		}
		~Node() {
			for (int i : {0, 1}) {
				if (child[i]) {
					delete child[i];
				}
			}
		}
	};

	Node *root;

	void inOrder(std::vector<S> &vals, Node *node) const {
		if (!node) {
			return;
		}
		inOrder(node->child[0]);
		vals.push_back(node->value);
		inOrder(node->child[1]);
	}

	void rotate(Node *node) {
		if (!node->parent) {
			return;
		}
		auto &parent = node->parent;
		int dir = Node::dir(node);
		parent->child[dir] = node->child[!dir];
		node->parent = parent->parent;
		node->child[!dir] = parent;
		Node::update(parent);
		Node::update(node);
	}

	void splay(Node *node, Node *parent = nullptr) {
		while (node->parent != parent) {
			if (node->parent->parent == parent) {
				rotate(node);
				return;
			}
			if (Node::dir(node) == Node::dir(node->parent)) {
				rotate(node->parent);
				rotate(node);
			} else {
				rotate(node);
				rotate(node);
			}
		}
	}

	Node *find(int i) {
		Node *current = root;
		while (current) {
			if (i < Node::getCount(current->child[0])) {
				current = current->child[0];
				continue;
			}
			i -= Node::getCount(current->child[0]);
			if (i == 0) {
				splay(current);
				return current;
			}
			i--;
			current = current->child[1];
		}
		return nullptr;
	}

	/**
	 * Splays the interval [l, r]
	 */
	Node *splayInterval(int l, int r) {
		int n = size();
		if (l == 0 && r + 1 == n) {
			return root;
		}
		if (l == 0) {
			auto R = find(r + 1);
			return R->child[0];
		}
		if (r + 1 == n) {
			auto L = find(l - 1);
			return L->child[1];
		}
		auto L = find(l - 1);
		auto R = find(r + 1);
		splay(L, R);
		return L->child[1];
	}
};

template <class T> class OrderedSplayTree {
  public:
	OrderedSplayTree() : root(nullptr) {}

	int size() { return getCount(root); }

	void insert(T value) {
		if (!root) {
			root = new Node(value);
		}
		auto &node = find(root, value);
		if (node == nullptr) {
			node = new Node(value);
		}
		splay(node);
	}

	void remove(T value) {
		auto &node = find(root, value);
		if (node == nullptr) {
			return;
		}
	}

	template <typename... Ts> void emplace(Ts... args) {
		insert(T(std::forward(args...)));
	}

  private:
	struct Node {
		T value;
		Node *child[2];
		Node *parent;
		int count;
		Node(T value) : value(value), parent(nullptr), count(1) {
			child[0] = child[1] = nullptr;
		}
	};

	Node *root;

	Node *&find(Node *&node, T value) {
		if (node == nullptr) {
			return node;
		}
		if (node->value == value) {
			return node;
		}
		if (value < node->value) {
			return find(node->child[0]);
		} else {
			return find(node->child[1]);
		}
	}

	Node *findIdx(Node *node, int idx) {
		if (getCount(node->child[0]) > idx) {
			return findIdx(node->child[0], idx);
		}
		idx -= getCount(node->child[0]);
		if (idx == 0) {
			return node;
		}
		return findIdx(node->child[1], idx);
	}

	static inline int getCount(Node *node) {
		if (!node) {
			return 0;
		}
		return node->count;
	}

	static inline void update(Node *node) {
		if (!node) {
			return;
		}
		node->count = 1 + getCount(node->child[0]) + getCount(node->child[1]);
	}

	static inline int dir(Node *node) {
		return node->parent && node->parent->child[1] == node;
	}

	void rotate(Node *node) {
		if (!node || !node->parent) {
			return;
		}
		auto &par = node->parent;
		int d = dir(node);
		node->parent = par->parent;
		par->parent->child[dir(par)] = node;
		par->parent = node;
		par->child[d] = node->child[!d];
		node->child[!d] = par;
		update(par);
		update(node);
	}

	void splay(Node *node, Node *par = nullptr) {
		while (node->parent != par) {
			if (node->parent->parent == par) {
				rotate(node);
				return;
			}
			if (dir(node) == dir(node->parent)) {
				rotate(node->parent);
				rotate(node);
			} else {
				rotate(node);
				rotate(node);
			}
		}
	}
};

}; // namespace mog::internal

#endif
