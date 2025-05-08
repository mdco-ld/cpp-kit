#ifndef _MO_LICHAO_HPP_
#define _MO_LICHAO_HPP_

#include <vector>
#include <limits>

namespace mo {

template <typename T = long long> class LiChao {
  public:
    struct Line {
		T a;
		T b;
		T operator()(T x) {
			return a * x + b;
		}
	};

    LiChao(T L, T R): L(L), R(R) {
	}

	void addLine(Line line) {
		if (root == -1) {
			root = makeNode(L, R, line);
			return;
		}
		addLine(line, root, L, R);
	}

	T operator()(T x) {
		return getMin(x, root);
	}

  private:
    struct Node {
		T L;
		T R;
		Line line;
		int left = -1;
		int right = -1;
		inline T mid() {
			return L + (R - L) / 2;
		}
	};

	int makeNode(int L, int R, Line line) {
		int n = t.size();
		t.emplace_back(L, R, line);
		return n;
	}

	void addLine(Line line, int v, int L, int R) {
		int m = t[v].mid();
		bool left = line(L) < t[v].line(L);
		bool mid = line(m) < t[v].line(m);
		if (mid) {
			std::swap(line, t[v].line);
		}
		if (R - L == 1) {
			return;
		}
		if (left != mid) {
			if (t[v].left == -1) {
				t[v].left = makeNode(L, m, line);
			} else {
				addLine(line, t[v].left, L, m);
			}
		} else {
			if (t[v].right == -1) {
				t[v].right = makeNode(m, R, line);
			} else {
				addLine(line, t[v].right, m, R);
			}
		}
	}

	T getMin(T x, int v) {
		if (v == -1) {
			return std::numeric_limits<T>::max();
		}
		int m = t[v].mid();
		if (t[v].R - t[v].L == 1) {
			return t[v].line(x);
		}
		if (x < m) {
			return std::min(t[v].line(x), getMin(x, t[v].left));
		} else {
			return std::min(t[v].line(x), getMin(x, t[v].right));
		}
	}

	int L;
	int R;
    std::vector<Node> t;
	int root = -1;
};

}; // namespace mo

#endif
