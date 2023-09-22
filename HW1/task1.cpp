#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

class Solution {
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end()); // sort to avoid duplicates like (1, 2, 1) and (1, 1, 2) in {1, 2, 1, 2}
    std::set<std::vector<int>> result;
    for (size_t i = 0; i < (1 << nums.size()); i++) { // 1 << nums.size - iterate over all subsets.
      // i % (2 << 6) == true means 6-th num presented in current subset
      result.insert(genSubset(nums, i));
    }
    return {result.begin(), result.end()};
  }

private:
  inline std::vector<int> genSubset(const std::vector<int> &nums, size_t idx) {
    std::vector<int> res;
    idx = idx << 1;
    // pick only numbers presented in idx subset representation
    std::copy_if(nums.begin(), nums.end(), std::back_inserter(res),
                 [&idx](const int& val) { return (idx = (idx >> 1)) % 2; }
    );
    return res;
  }
};
