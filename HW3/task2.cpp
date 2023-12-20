#include <vector>

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
        auto xor1 = 0;
        for (const auto &el: nums) {
          xor1 ^= el;
        }
        auto diff_bit = 0;
        while (((xor1 >> (diff_bit)) % 2) == 0) {
          diff_bit++;
        }
        auto el1 = 0;
        auto el2 = 0;
        for (const auto &el: nums) {
            if (((el >> diff_bit) % 2) == 0) {
                el1 ^= el;
            } else {
                el2 ^= el;
            }
        }
        std::vector<int> res = {};
        res.emplace_back(el1);
        res.emplace_back(el2);
        return res;
    }
};

int main() {
    std::vector<int> in{1, 2, 1, 3, 2, 5};
    Solution().singleNumber(in);
}