//
// Created by aleksey on 11.12.2023.
//

#include <vector>
#include <algorithm>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include <boost/graph/graphviz.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

class Solution {
  class DSU {
  public:
    DSU(int n) : weight(0) {
      parent.resize(n);
      for (int i = 0; i < n; i++) {
        parent[i] = i;
      }
    }

    void unite(int a, int b, int w) {
      a = find_set(a);
      b = find_set(b);
      if (a != b) {
        weight += w;
        parent[b] = a;
      }
    }

    int find_set (int v) {
      if (v == parent[v])
        return v;
      return parent[v] = find_set(parent[v]);
    }

    std::vector<int> parent;
    long long weight = 0;
  };

public:
  std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, std::vector<std::vector<int>>& edges) {
    /**
     * 1. Build mst for whole graph using DSU & Kruskal algorithm
     * 2. For all edges:
     *        try to remove one and compare mst without it with original (and validate for it's existing)
     */
    DSU a(n);
    auto orig_edges = edges;
    std::sort(edges.begin(), edges.end(), [](auto &e1, auto &e2){
      return e1[2] < e2[2];
    });
    for (const auto &edge: edges) {
      auto from = edge[0];
      auto to = edge[1];
      auto w = edge[2];
      a.unite(from, to, w);
    }
    auto mst = a.weight;
    std::vector<int> critical;
    std::vector<int> pseudo_critical;

    for (int i = 0; i < orig_edges.size(); i++) {
      const auto &remove = orig_edges[i];
      DSU b(n);
      DSU c(n);
      c.unite(remove[0], remove[1], remove[2]);
      // todo: right now it's not optimal. We just directly remove edge and check what happens with mst.
      for (auto edge: edges) {
        if (edge == remove) {
          continue;
        } else {
          b.unite(edge[0], edge[1], edge[2]);
          c.unite(edge[0], edge[1], edge[2]);
        }
      }
      auto common = b.find_set(0);
      bool mst_exist = true;
      for (int l = 0; l < n; l++) {
        if (b.find_set(l) != common) {
          critical.emplace_back(i);
          mst_exist = false;
          break;
        }
      }
      if (!mst_exist) {
        continue;
      }
      if (mst < b.weight) {
        critical.emplace_back(i);
      } else if (mst == c.weight) {
        pseudo_critical.emplace_back(i);
      }
    }
    return {critical, pseudo_critical};
  }
};

int main(int argc, char **argv) {
  CLI::App app{"App for finding critical and pseudo-critical edges"};

  std::string inputGraph;
  app.add_option("-i,--inputGraph", inputGraph, "Path to input graph")->required();
  std::optional<std::string> outputGraph;
  app.add_option("-o,--outputGraph.dot", outputGraph, "Path to output graph");
  std::optional<std::string> outputMst;
  app.add_option("--outputMst.dot", outputMst, "Path to output MST");
  std::optional<std::string> criticalEdges;
  app.add_option("--outputCriticalAndPseudocriticalEdges.dot", criticalEdges, "Path to critical and pseudo-critical edges result");

  CLI11_PARSE(app, argc, argv);

  std::ifstream reader(inputGraph);
  int n, m;
  reader >> n >> m;

  using Graph = boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property< boost::edge_weight_t, int > >;
  using Edge = boost::graph_traits<Graph>::edge_descriptor;
  using E = std::pair<int, int>;
  std::vector<E> edges;
  std::vector<int> weights;
  for (int i = 0; i < m; i++) {
    int from, to, weight;
    reader >> from >> to >> weight;
    edges.emplace_back(from, to);
    weights.emplace_back(weight);
  }
  Graph graph(edges.begin(), edges.end(), weights.begin(), n);

  auto weight = get(boost::edge_weight, graph);
  std::vector< Edge > spanning_tree;

  kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));

  std::vector<int> mst_weights;
  std::vector<E> mst_edges;
  for (auto ei: spanning_tree)
  {
    mst_weights.emplace_back(weight[ei]);
    mst_edges.emplace_back(boost::source(ei, graph), boost::target(ei, graph));
  }

  Graph mst(mst_edges.begin(), mst_edges.end(), mst_weights.begin(), n);
  std::vector<std::string> names;
  std::vector<const char *> names_ref;
  names.reserve(n);
  for (int i = 0 ; i < n; i++) {
    names.emplace_back(std::to_string(i));
    names_ref.emplace_back(names.back().data());
  }
  if (outputGraph) {
    auto out = std::ofstream(*outputGraph);
    boost::write_graphviz(out, graph, boost::make_label_writer(names_ref.data()));
  }
  if (outputMst) {
    auto out = std::ofstream(*outputGraph);
    boost::write_graphviz(out, mst, boost::make_label_writer(names_ref.data()));
  }
  // todo: Boost disgusting
}
