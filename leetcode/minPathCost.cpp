/**********************************************
  > File Name		: minPathCost.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Aug  9 17:24:28 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& _moveCost) {
        const int m = grid.size(), n = grid[0].size();
        auto dp = grid;

        vector<vector<int>> moveCost(m*n, vector<int>(n, 0));

        for (int i = 0; i < m-1; i++) {
            const auto& row = grid[i], next_row = grid[i+1];
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    moveCost[next_row[k]][j] = _moveCost[row[j]][k];
                }
            }
        }

        vector<int> cost(n);
        for (int i = 1; i < m; i++) {
            for (int k = 0; k < n; k++) {
                const auto& mc_row = moveCost[grid[i][k]];
                const auto& dp_prev_row = dp[i-1];
                std::transform(dp_prev_row.cbegin(), dp_prev_row.cend(), mc_row.cbegin(), cost.begin(), std::plus<int>());

                dp[i][k] += *std::min_element(cost.cbegin(), cost.cend());
            }
        }
        return *std::min_element(dp[m-1].cbegin(), dp[m-1].cend());
    }
};

int main() {
}
