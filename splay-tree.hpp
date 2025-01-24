#ifndef _MO_SPARSE_TABLE_
#define _MO_SPARSE_TABLE_

#include <algorithm>
#include <cstdint>

namespace MO {

namespace ds {

using std::size_t;

template <typename T, T (*op)(T, T)> class SplayTree {

  public:
    struct Node {
        size_t size;
        Node *parent;
        Node *child[2];
        T value;
        T prod;
        bool mirror;
        Node(T value)
            : size(1), value(value), parent(nullptr), prod(value),
              mirror(false) {
            child[0] = child[1] = nullptr;
        }
        ~Node() {
            for (int i = 0; i < 2; i++) {
                if (child[i] != nullptr) {
                    delete child[i];
                }
            }
        }
    };

    SplayTree() : root(nullptr) {}
    ~SplayTree() { delete root; }

    void pushDownAll() { pushDownAll(root); }

    void update(Node *node) {
        pushDown(node);
        if (node == nullptr) {
            return;
        }
        node->size = 1;
        node->prod = node->value;
        for (int i = 0; i < 2; i++) {
            if (node->child[i] != nullptr) {
                node->size += node->child[i]->size;
                node->prod = op(node->prod, node->child[i]->prod);
            }
        }
    }

    Node *find(size_t position, bool shouldSplay = true) {
        Node *current = root;
        while (true) {
            pushDown(current);
            size_t leftSize = current->child[0] ? current->child[0]->size : 0;
            if (position == leftSize) {
                break;
            }
            if (position < leftSize) {
                current = current->child[0];
            } else {
                position -= leftSize + 1;
                current = current->child[1];
            }
        }
        if (shouldSplay) {
            splay(current);
        }
        return current;
    }

    void insert(T value, size_t position) { insert(new Node(value), position); }

    void insert(Node *node, size_t position) {
        if (root == nullptr) {
            root = node;
            return;
        }
        Node *current = root;
        while (true) {
            pushDown(current);
            size_t leftSize = current->child[0] ? current->child[0]->size : 0;
            if (position > leftSize) {
                position -= leftSize + 1;
                if (current->child[1] == nullptr) {
                    current->child[1] = node;
                    current->child[1]->parent = current;
                    break;
                }
                current = current->child[1];
            } else {
                if (current->child[0] == nullptr) {
                    current->child[0] = node;
                    current->child[0]->parent = current;
                    break;
                }
                current = current->child[0];
            }
        }
        while (current != nullptr) {
            update(current);
            current = current->parent;
        }
    }

    void rotate(Node *node) {
        Node *parent = node->parent;
        if (!parent) {
            return;
        }
        int direction = getUpDirection(node);
        if (parent->parent != nullptr) {
            int parentDirection = !getUpDirection(parent);
            parent->parent->child[parentDirection] = node;
        }
        if (node->child[direction]) {
            node->child[direction]->parent = parent;
        }
        node->parent = parent->parent;
        parent->parent = node;
        parent->child[!direction] = node->child[direction];
        node->child[direction] = parent;
        update(parent);
        update(node);
    }

    void splay(Node *node, Node *above = nullptr) {
        while (node->parent != above) {
            Node *parent = node->parent;
            if (parent->parent == above) {
                rotate(node);
                continue;
            }
            if (getUpDirection(node) == getUpDirection(parent)) {
                rotate(parent);
                rotate(node);
            } else {
                rotate(node);
                rotate(node);
            }
        }
        if (above == nullptr) {
            root = node;
        }
    }

    Node *splayInterval(size_t l, size_t r) {
        size_t n = root->size;
        if (r < l + 1) {
            return nullptr;
        }
        if (l == 0 && r >= n) {
            return root;
        }
        if (l == 0) {
            Node *R = find(r);
            return R->child[0];
        }
        if (r >= n) {
            Node *L = find(l - 1);
            return L->child[1];
        }
        Node *R = find(r, false);
        Node *L = find(l - 1, false);
        splay(R);
        splay(L, R);
        return L->child[1];
    }

    Node *remove(Node *node) {
        if (!node) {
            return node;
        }
        if (node == root) {
            root = nullptr;
            return node;
        }
        int direction = !getUpDirection(node);
        node->parent->child[direction] = nullptr;
        update(node->parent);
        node->parent = nullptr;
        return node;
    }

    T prod(size_t l, size_t r) { return splayInterval(l, r)->prod; }

    void flip(size_t l, size_t r) {
        if (r <= l + 1) {
            return;
        }
        Node *interval = splayInterval(l, r);
        interval->mirror = !interval->mirror;
    }

    size_t size() {
        if (root == nullptr) {
            return 0;
        }
        return root->size;
    }

  private:
    void pushDown(Node *node) {
        if (!node) {
            return;
        }
        if (node->mirror) {
            std::swap(node->child[0], node->child[1]);
        }
        for (int i = 0; i < 2; i++) {
            if (node->child[i] != nullptr) {
                node->child[i]->mirror ^= node->mirror;
            }
        }
        node->mirror = false;
    }

    void pushDownAll(Node *node) {
        if (node == nullptr) {
            return;
        }
        pushDown(node);
        for (int i = 0; i < 2; i++) {
            pushDownAll(node->child[i]);
        }
    }

    inline int getUpDirection(Node *node) {
        return node->parent->child[0] == node;
    }

    Node *root;
};

}; // namespace ds

}; // namespace MO

#endif
