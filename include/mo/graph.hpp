#ifndef _MO_GRAPH_HPP_
#define _MO_GRAPH_HPP_

#include <numeric>
#include <optional>
#include <queue>
#include <vector>

namespace mo {

template <typename T, bool isDirected = false> class Graph {
  private:
    std::vector<std::vector<T>> edges;

  public:
    Graph(int n) : edges(n + 1) {}

    void addEdge(T u, T v) {
        edges[u].push_back(v);
        if constexpr (!isDirected) {
            edges[v].push_back(u);
        }
    }

    std::vector<T> &operator[](T u) { return edges[u]; }
};

template <typename T, typename Distance, bool isDirected = false> class WGraph {
  private:
    struct DistType {
      private:
        std::optional<Distance> val;

      public:
        DistType() : val() {}
        DistType(Distance d) : val(d) {}
        inline bool isFinite() const { return val.has_value(); }
        inline Distance value() const { return val.value(); }
        inline DistType operator+(const DistType &other) const {
            if (!isFinite() || !other.isFinite()) {
                return DistType{};
            }
            return DistType{value() + other.value()};
        }
        bool operator<(const DistType &other) const {
            if (!isFinite()) {
                return false;
            }
            if (!other.isFinite()) {
                return true;
            }
            return val < other.val;
        }
    };

    std::vector<std::vector<std::pair<Distance, T>>> edges;
    int n;

  public:
    WGraph(int n) : n(n), edges(n + 1) {}

    void addEdge(T u, T v, Distance w) {
        edges[u].push_back({w, v});
        if constexpr (!isDirected) {
            edges[v].push_back({v, w});
        }
    }

    std::vector<DistType> getDistances(T source) {
        std::priority_queue<std::pair<DistType, T>,
                            std::vector<std::pair<DistType, T>>,
                            std::greater<std::pair<DistType, T>>>
            q;
        q.push({Distance{}, source});
        std::vector<DistType> dist(n + 1);
        while (q.size()) {
            auto [d, u] = q.top();
            q.pop();
            if (!(d < dist[u])) {
                continue;
            }
            dist[u] = d;
            for (auto [w, v] : edges[u]) {
                if (DistType{w} + d < dist[v]) {
                    q.push({d + w, v});
                }
            }
        }
        return dist;
    }

    std::pair<std::vector<DistType>, std::vector<T>>
    getShortestPaths(T source) {
        std::priority_queue<std::tuple<DistType, T, T>,
                            std::vector<std::tuple<DistType, T, T>>,
                            std::greater<std::tuple<DistType, T, T>>>
            q;
        q.push({Distance{}, source, source});
        std::vector<DistType> dist(n + 1);
        std::vector<T> previous(n + 1);
        std::iota(previous.begin(), previous.end(), T{});
        while (q.size()) {
            auto [d, u, p] = q.top();
            q.pop();
            if (!(d < dist[u])) {
                continue;
            }
            dist[u] = d;
            previous[u] = p;
            for (auto [w, v] : edges[u]) {
                if (DistType{w} + d < dist[v]) {
                    q.push({d + w, v, u});
                }
            }
        }
        return {dist, previous};
    }

    std::vector<std::pair<Distance, T>> &operator[](T u) { return edges[u]; }
};

}; // namespace mo

#endif
