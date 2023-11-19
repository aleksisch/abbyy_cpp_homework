//
// Created by aleksey on 13.10.2023.
//

#include <vector>

class Solution {
public:
  int trap(vector<int>& height) {
    int res = 0;
    int acc = 0;
    int prev_ma = 0;
    for (const auto &x: height) {
      if (x < prev_ma) {
        acc += prev_ma - x;
      } else {
        res += acc;
        acc = 0;
        prev_ma = x;
      }
    }
    int last_ma = 0;
    if (height.back() >= prev_ma) {
      res += acc;
    }
    for (auto it = height.rbegin(); it != height.rend(); ++it) { // no ranges on leetcode :(
      const auto &x = *it;
      if (x == prev_ma) {
        break;
      } else if (x <= last_ma) {
        res += last_ma - x;
      } else {
        last_ma = x;
      }
    }
    return res;
  }
};

int main() {
  std::cout << Solution().trap(std::vector<int>{0,1,0,2,1,0,1,3,2,1,2,1});
}