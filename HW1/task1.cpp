//
// Created by aleksey on 08.10.2023.
//

#include <vector>
#include <set>

class Solution {
public:
  std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
    result = {};
    sz = nums.size();
    std::vector<int> empty;
    genPermute(empty, nums);
    return {result.begin(), result.end()};
  }

private:
  void genPermute(std::vector<int> &curr, std::vector<int> &remains) {
    if (curr.size() == sz) {
      result.insert(curr);
      return;
    }

    for (size_t i = 0; i < remains.size(); i++) { // iterate over remaining elements
      auto el = remains[i];
      curr.emplace_back(el); // add new element to current permutation
      std::swap(remains[i], remains.back());  // in next 2 lines we efficiently remove it from vector
      remains.pop_back();
      genPermute(curr, remains);
      remains.emplace_back(el); // in next 3 lines we revert previous changes
      std::swap(remains[i], remains.back());
      curr.pop_back();
    }
  }

private:
  std::set<std::vector<int>> result;
  size_t sz;
};

int main() {
  auto tmp = std::vector<int>{1, 3, 2};
  auto res = Solution().permuteUnique(tmp);
  res.size();
}