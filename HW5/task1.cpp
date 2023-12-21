//
// Created by aleksey on 10.12.2023.
//

class Solution {
public:
  int characterReplacement(string s, int k) {
    // Just memory optimization
    // std::unordered_map<char, int> curr;
    int curr[28] = {};
    int max_freq = 0;
    int result = 0;
    for (int start = 0, end = 0; end < s.size(); end++) {
      curr[s[end] - 'A']++;
      max_freq = std::max(max_freq, curr[s[end] - 'A']);
      while ((end - start + 1) - max_freq > k) {
        curr[s[start] - 'A']--;
        start++;
      }
      result = std::max(end - start + 1, result);
    }
    return result;
  }
};


int main() {
  std::cout << Solution().characterReplacement("ABAB", 2);
}