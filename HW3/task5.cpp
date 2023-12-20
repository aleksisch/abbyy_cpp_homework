//
// Created by aleksey on 04.11.2023.
//


#include <unordered_map>
#include <unordered_set>
#include <vector>

struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

class Solution {
  using Graph = std::unordered_map<int, std::unordered_set<int>>;
  using EdgeT = std::pair<int, int>;

  std::vector<int> visited;
  std::unordered_map<EdgeT, int, pairhash> idx;
  Graph graph;
public:
  std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>>& edges) {
    /**
     * Main idea:
     * `in_two` - vertex with 2 incoming edges.
     * If exists loop => it contains extra vertex, find it using input and `in_two` if it is not empty
     * otherwise `in_two` exists => just find last edge (from, to) with `to` vertex.
     */
    std::vector<int> maybe_twice(edges.size(), 0);
    int ma = 0;
    std::optional<int> in_two;
    for (const auto &edge: edges) {
      auto from = edge.front();
      auto to = edge.back();
      graph[from].emplace(to);
      idx.emplace(std::make_pair(from, to), idx.size());
      ma = std::max(ma, std::max(from, to));
      if (maybe_twice[to] != 0) {
        in_two.emplace(to);
      }
      maybe_twice[to]++;
    }
    visited.resize(ma + 1, -1);
    for (const auto &[from, tos] : graph) {
      std::vector<EdgeT> loop_edges;
      const auto is_loop = findLoop(from, loop_edges);
      if (is_loop || !loop_edges.empty()) {
        EdgeT ma_edge = {-1, -1};
        int ma_index = -1;
        for (const auto &edge : loop_edges) {
          if (idx[edge] > ma_index && in_two.value_or(edge.second) == edge.second) {
            ma_edge = edge;
            ma_index = idx[edge];
          }
        }
        return {ma_edge.first, ma_edge.second};
      }
    }

    EdgeT ma_edge = {-1, -1};
    int ma_index = -1;
    for (const auto &edge : edges) {
      auto edge_t = std::make_pair(edge.front(), edge.back());
      if (edge.back() == in_two.value() && idx[edge_t] > ma_index) {
        ma_edge = edge_t;
        ma_index = idx[edge_t];
      }
    }
    graph.clear();
    visited.clear();
    return {ma_edge.first, ma_edge.second};
  }

private:

  /**
   * Tries to find loop
   * @param edge begin edge
   * @param loop_edges result loop edges
   * @return for internal purposes.
   */
  bool findLoop(int edge, std::vector<EdgeT> &loop_edges) {
    if (visited[edge] == 0) {
      visited[edge] = 1;
      return true;
    } else if (visited[edge] == 1) {
      return false;
    }
    visited[edge] = 0;
    for (const auto to: graph[edge]) {
      auto in_loop = findLoop(to, loop_edges);
      if (in_loop || !loop_edges.empty()) {
        if (in_loop) {
          loop_edges.emplace_back(edge, to);
        }
        return visited[edge] == 0;
      }
    }
    visited[edge] = 1;
    return false;
  }
};

int main() {
  std::vector<std::vector<int>> inp = {{1, 2}, {2, 3}, {3, 1}, {4, 1}};
  Solution().findRedundantDirectedConnection(inp);
}