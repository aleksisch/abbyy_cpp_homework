class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        std::unordered_set<int> met;
        for (const auto &x: nums) {
            if (met.count(x)) {
                met.erase(x);
            } else {
                met.emplace(x);
            }
        }
        return {met.begin(), met.end()};
    }
};
