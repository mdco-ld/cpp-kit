#ifndef _MO_TREE_ALL_ROOTS_HPP_
#define _MO_TREE_ALL_ROOTS_HPP_

#include <mo/tree/tree.hpp>

#include <functional>
#include <optional>
#include <vector>

namespace mo {

namespace tree {

template <typename ValueType, typename T, bool oneBased>
std::vector<ValueType>
allRoots(const Tree<T, oneBased> &t, const std::vector<ValueType> &value,
         std::function<ValueType(ValueType, ValueType)> combine,
         std::function<ValueType(ValueType, ValueType)> join) {
    std::vector<ValueType> result(value.begin(), value.end());
    std::function<void(T, T)> baseDfs = [&](T v, T par) {
        for (T x : t[v]) {
            if (x == par) {
                continue;
            }
            baseDfs(x, v);
            ValueType joined = join(value[v], result[x]);
            result[v] = combine(result[v], joined);
        }
    };
    std::function<void(T, T, std::optional<ValueType>)> dfs =
        [&](T v, T par, std::optional<ValueType> acc) {
            if (acc.has_value()) {
                result[v] = combine(result[v], join(value[v], acc.value()));
            }
            int n = t[v].size();
            std::vector<ValueType> suffix(n);
            ValueType base =
                acc.has_value() ? join(value[v], acc.value()) : value[v];
            suffix[n - 1] = value[v];
            for (int i = n - 1; i > 0; i--) {
                if (t[v][i - 1] == par) {
                    suffix[i - 1] = suffix[i];
                } else {
                    suffix[i - 1] =
                        combine(suffix[i], join(value[v], result[t[v][i]]));
                }
            }
            ValueType pref = base;
            for (int i = 0; i < n; i++) {
                if (t[v][i] == par) {
                    continue;
                }
				ValueType tmp = join(value[v], result[t[v][i]]);
                dfs(t[v][i], v, combine(pref, suffix[i]));
                pref = combine(pref, tmp);
            }
        };
    if constexpr (oneBased) {
        baseDfs(T{1}, T{0});
        dfs(T{1}, T{0}, std::nullopt);
    } else {
        baseDfs(T{0}, T{t.size()});
        dfs(T{0}, T{t.size()}, std::nullopt);
    }
    return result;
}

}; // namespace tree

}; // namespace mo

#endif
