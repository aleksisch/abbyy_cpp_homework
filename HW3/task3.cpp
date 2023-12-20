//
// Created by aleksey on 04.11.2023.
//

#include <vector>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  std::vector<TreeNode*> generateTrees(int n) {
    std::vector<int> remains;
    for (int i = 0; i < n; i++) {
      remains.emplace_back(i + 1);
    }
    return genSubtree(remains);
  }
private:
  std::vector<TreeNode*> genSubtree(std::vector<int> &subtree) {
    if (subtree.size() == 0) {
      return {nullptr};
    } else if (subtree.size() == 1) {
      return {new TreeNode(subtree.front())};
    }
    std::vector<TreeNode*> result;
    for (const auto &root : subtree) {
      std::vector<int> left;
      std::copy_if (subtree.begin(), subtree.end(), std::back_inserter(left), [root](int i) {return i < root;});
      std::vector<int> right;
      std::copy_if (subtree.begin(), subtree.end(), std::back_inserter(right), [root](int i) {return i > root;});
      auto leftSubtree = genSubtree(left);
      auto rightSubtree = genSubtree(right);
      for (const auto leftRoot : leftSubtree) {
        for (const auto rightRoot : rightSubtree) {
          result.emplace_back(new TreeNode(root, leftRoot, rightRoot));
        }
      }
    }
    return result;
  }

};
