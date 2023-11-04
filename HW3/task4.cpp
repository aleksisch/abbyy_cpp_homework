class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        size_t res = 0;
        const auto x_sz = grid.size();
        const auto y_sz = grid.front().size();
        std::queue<std::pair<int, int>> dfs;
        for (long long i = 0; i < x_sz; i++) {
            for (long long l = 0; l < y_sz; l++) {
                if (grid[i][l] == '1') {
                    res++;
                    grid[i][l] = '0';
                    dfs.emplace(i, l);
                    while (!dfs.empty()) {
                        auto [x, y] = dfs.front();
                        dfs.pop();
                        handle(dfs, grid, x, y - 1);
                        handle(dfs, grid, x, y + 1);
                        handle(dfs, grid, x + 1, y);
                        handle(dfs, grid, x - 1, y);
                    }
                }
            }
        }
        return res;
    }

    void handle(std::queue<std::pair<int, int>>& dfs, vector<vector<char>>& grid, long long x, long long y) {
        if (constraint(grid, x, y) && grid[x][y] == '1') {
            grid[x][y] = '0';
            dfs.emplace(x, y);
        }
    }

    bool constraint(const vector<vector<char>>& grid, long long x, long long y) const {
        return x >= 0 && y >= 0 && x < grid.size() && y < grid.front().size();
    }
};
