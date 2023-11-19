//
// Created by aleksey on 19.11.2023.
//

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <iostream>

struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

class Solution {
  using WeightT = long long;
  using VertexId = int;
  using Graph = std::unordered_map<VertexId, std::unordered_map<VertexId, WeightT>>;
public:
  long long minimumWeight(int n, std::vector<std::vector<int>>& edges, int src1, int src2, int dest) {
    Graph g;
    Graph reversed_g;
    for (const auto &edge: edges) {
      if (!g[edge[0]].count(edge[1]) || g[edge[0]][edge[1]] > edge[2]) {
        g[edge[0]][edge[1]] = edge[2];
        reversed_g[edge[1]][edge[0]] = edge[2];
      }
    }
    for (int i = 0; i < n; i++) {
      g[i];
      reversed_g[i];
    }
    auto w1 = runDijkstra(g, src1);
    auto w2 = runDijkstra(g, src2);
    auto w3 = runDijkstra(reversed_g, dest);
    const auto max_value = static_cast<long long>(n) * 1000000000;
    WeightT result = max_value;
    for (int i = 0; i < n; i++) {
      if (!(w1.count(i) && w2.count(i) && w3.count(i))) {
        continue;
      } else {
        std::cout << w1[i] + w2[i] + w3[i] << std::endl;
        result = std::min(w1[i] + w2[i] + w3[i], result);
      }
    }
    if (result == max_value) {
      return -1;
    } else {
      return result;
    }
  }

private:
  std::unordered_map<VertexId, WeightT> runDijkstra(const Graph &g, int v1) {
    std::unordered_set<VertexId> visited;
    std::unordered_map<VertexId, WeightT> result;
    std::multimap<WeightT, VertexId> scheduled;
    scheduled.emplace(0, v1);
    while (!scheduled.empty()) {
      auto [w, v] = *scheduled.begin();
      scheduled.erase(scheduled.begin());
      if (visited.count(v)) {
        continue;
      }
      result.emplace(v, w);
      visited.emplace(v);
      for (const auto &[to_v, to_w]: g.at(v)) {
        if (visited.count(to_v)) {
          continue;
        }
        scheduled.emplace(to_w + w, to_v);
      }
    }
    return std::move(result);
  }
};

int main() {
  std::vector<std::vector<int>> graph = {

    {9,3,68},
    {3,5,77},

    {35,79,90},
    {79,5,42},

    {35,65,11},
    {65,5,56},

    {9,5,90},

    {35,25,67},
    };
  std::cout << Solution().minimumWeight(81, graph, 35, 9, 5) << std::endl;
}