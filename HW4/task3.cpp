//
// Created by aleksey on 19.11.2023.
//

#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>
#include <unordered_map>

class Solution {
  using WeightT = int;
  using VertexId = int;
  using VertexT = std::vector<VertexId>;
public:
  int minCostConnectPoints(std::vector<std::vector<int>>& points) {
    std::multimap<WeightT, VertexId> q;
    std::unordered_map<VertexId, WeightT> curr; // for optimisation purpose to skip vertexes with lower weight
    q.emplace(0, 0);
    std::unordered_set<VertexId> remains;
    for (int i = 0; i < points.size(); i++) {
      remains.emplace(i);
    }
    WeightT result = 0;
    while (!q.empty()) {
      auto [w, v] = *(q.begin());
      q.erase(q.begin());
      curr.erase(v);
      if (!remains.count(v)) {
        continue;
      }
      result += w;
      remains.erase(v);
      for (const auto &i: remains) {
        const auto cur_dist = dist(points[v], points[i]);
        if (curr.count(i) && curr[i] < cur_dist) {
          continue;
        }
        q.emplace(cur_dist, i);
        curr[i] = cur_dist;
      }
    }
    return result;
  }
private:
  WeightT dist(const VertexT &v1, const VertexT& v2) {
    return std::abs(v1.front() - v2.front()) + std::abs(v1.back() - v2.back());
  }
};

int main() {
  std::vector<std::vector<int>> points {{0,0},{2,2},{3,10},{5,2},{7,0}};
  std::cout << Solution().minCostConnectPoints(points) << std::endl;
}