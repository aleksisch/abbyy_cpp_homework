#include <vector>
#include <queue>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        size_t res = 0;
        const auto x_sz = grid.size();
        const auto y_sz = grid.front().size();
        std::queue<std::pair<int, int>> bfs;
        for (long long x = 0; x < x_sz; x++) {
            for (long long y = 0; y < y_sz; y++) {
                if (grid[x][y] == '1') {
                    res++;
                    grid[x][y] = '0';
                    bfs.emplace(x, y);
                    while (!bfs.empty()) {
                        auto [new_x, new_y] = bfs.front();
                        bfs.pop();
                        handle(bfs, grid, new_x, new_y - 1);
                        handle(bfs, grid, new_x, new_y + 1);
                        handle(bfs, grid, new_x + 1, new_y);
                        handle(bfs, grid, new_x - 1, new_y);
                    }
                }
            }
        }
        return res;
    }

    void handle(std::queue<std::pair<int, int>>& bfs, std::vector<std::vector<char>>& grid, long long x, long long y) {
        if (constraint(grid, x, y) && grid[x][y] == '1') {
            grid[x][y] = '0';
            bfs.emplace(x, y);
        }
    }

    bool constraint(const std::vector<std::vector<char>>& grid, long long x, long long y) const {
        return x >= 0 && y >= 0 && x < grid.size() && y < grid.front().size();
    }
};
