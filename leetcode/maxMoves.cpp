#include <vector>
using namespace std;

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();
        vector<vector<int>> cache(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) cache[i][n-1] = 1;

        std::function<int(int, int)> backtrace = [&](int row, int col) {
            if (cache[row][col]) return cache[row][col];

            int sub_max = 0;
            const int cur = grid[row][col];
            if (row > 0 && cur < grid[row-1][col+1])
                sub_max = max(sub_max, backtrace(row-1, col+1));
            if (cur < grid[row][col+1])
                sub_max = max(sub_max, backtrace(row, col+1));
            if (row < m-1 && cur < grid[row+1][col+1])
                sub_max = max(sub_max, backtrace(row+1, col+1));

            cache[row][col] = sub_max+1;
            return sub_max+1;
        };

        int res = 0;
        for (int i = 0; i < m; i++) res = max(res, backtrace(i, 0));
        return res;
    }
};
