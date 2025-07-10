#ifndef _MO_ARRAY_HPP_
#define _MO_ARRAY_HPP_

#include <mo/internal/splay-tree.hpp>

namespace mo {

template <class T> class Array {
    using Impl = internal::SplayTree<T>;

  public:
    void insertBack(T value) { st.insertBack(value); }

    template <typename... Ts> void emplaceBack(Ts... args) {
        st.emplaceBack(std::forward(args...));
    }

	T &operator[](int idx) {
		return st[idx];
	}

	void remove(int idx) {
		st.remove(idx);
	}

	void removeInterval(int l, int r) {
		st.extractInterval(l, r);
	}

  private:
    Impl st;
};

template <mo::internal::traits::Monoid S> class MonoidArray {
    using Impl = internal::SplayTreeMonoid<S>;

  public:
    void insertBack(S value) { st.insertBack(value); }

    template <typename... Ts> void emplaceBack(Ts... args) {
        st.emplaceBack(std::forward(args...));
    }

  private:
    Impl st;
};

}; // namespace mo

#endif
