#ifndef _MOG_ARRAY_HPP_
#define _MOG_ARRAY_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/splay-tree.hpp>

namespace mog {

template <class T> class Array {
	using Impl = internal::SplayTree<T>;

  public:
	void insertBack(T value) { st.insertBack(value); }

	template <typename... Ts> void emplaceBack(Ts... args) {
		st.emplaceBack(std::forward(args...));
	}

	T &operator[](int idx) { return st[idx]; }

	void remove(int idx) { st.remove(idx); }

	void removeInterval(int l, int r) { st.extractInterval(l, r); }

  private:
	Impl st;
};

template <mog::internal::traits::Monoid S> class MonoidArray {
	using Impl = internal::SplayTreeMonoid<S>;

  public:
	void insertBack(S value) { st.insertBack(value); }

	template <typename... Ts> void emplaceBack(Ts... args) {
		st.emplaceBack(std::forward(args...));
	}

  private:
	Impl st;
};

}; // namespace mog

#endif
