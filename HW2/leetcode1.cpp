//
// Created by aleksey on 14.10.2023.
//

#include <vector>
#include <string>
#include <iostream>

class Solution {
public:
  bool isInterleave(std::string s1, std::string s2, std::string s3) {
    if (s1.size() + s2.size() != s3.size()) {
      return false;
    }

    // if we can create prefix of s3 by mixing i-prefix s1 and j-prefix s2 then dp[i][j] = true
    // due to memory optimization we omit whole dp matrix and store 2 last lines instead.
    std::vector<bool> prev(s2.size() + 1, false);
    std::vector<bool> cur(s2.size() + 1, false);

    prev[0] = true;
    for (int i = 0; i < s1.size() + 1; i++) {
      for (size_t j = 0; j < s2.size() + 1; j++) {
        if (i != s1.size()) {
          auto add_s1 = (s1[i] == s3[i + j]) && prev[j];
          cur[j] = add_s1;
        }
        if (j != s2.size()) {
          auto add_s2 = (s2[j] == s3[i + j]) && prev[j];
          prev[j + 1] = prev[j + 1] || add_s2;
        }
      }
      if (i != s1.size()) {
        prev = cur;
      }
    }
    return prev.back();
  }
};

int main() {
  std::cout << Solution().isInterleave("a", "b", "ab");
}