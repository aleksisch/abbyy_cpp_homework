class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mi = 100000 + 1;
        int res = 0;
        for (auto &p : prices) {
            res = std::max(p - mi, res);
            if (p < mi) {
                mi = p;
            }
        }
        return res;
    }
};
