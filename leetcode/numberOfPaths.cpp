/**********************************************
  > File Name		: numberOfPaths.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Oct 10 17:28:44 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    int numberOfPaths(vector<vector<int>> &grid, int k) {
        const int mod = 1e9 + 7;
        int m = grid.size(), n = grid[0].size(), f[m + 1][n + 1][k];
        memset(f, 0, sizeof(f));
        f[0][1][0] = 1;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                for (int v = 0; v < k; ++v)
                    f[i + 1][j + 1][(v + grid[i][j]) % k] = (f[i + 1][j][v] + f[i][j + 1][v]) % mod;
        return f[m][n][0];
    }
};


