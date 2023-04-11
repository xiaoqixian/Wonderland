/**********************************************
  > File Name		: minimumVisitedCells.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Apr 10 22:22:44 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
#include <queue>
#include <variant>
using namespace std;

class Solution {
public:
    int minimumVisitedCells(const vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();
        if (m == 1 && n == 1) return 1;
        queue<tuple<int, int, int>> q;
        vector<int> row_visited(m, 0), col_visited(n, 0);
        vector<int> row_reached(m, 0), col_reached(n, 0);
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int res = INT_MAX;
        q.push({0, 0, 1});
        visited[0][0] = true;

        while (!q.empty()) {
            const auto [i, j, dist] = q.front();
            q.pop();
            if (!grid[i][j]) continue;

            const int j_limit = min(grid[i][j]+j, n-1), 
                      i_limit = min(grid[i][j]+i, m-1);

            if (j < row_reached[i]) {
                for (int k = j+1; k <= j_limit; k++) {
                    if (i == m-1 && k == n-1) res = min(res, dist+1);
                    if (visited[i][k]) continue;
                    visited[i][k] = true;
                    q.push({i, k, dist+1});
                }
            } else {
                row_reached[i] = j;
                for (int k = max(row_visited[i]+1, j+1); k <= j_limit; k++) {
                    if (i == m-1 && k == n-1) res = min(res, dist+1);
                    if (visited[i][k]) continue;
                    visited[i][k] = true;
                    q.push({i, k, dist+1});
                }
                row_visited[i] = max(row_visited[i], j_limit);
            }

            if (i < col_reached[j]) {
                for (int k = i+1; k <= i_limit; k++) {
                    if (k == m-1 && j == n-1) res = min(res, dist+1);
                    if (visited[k][j]) continue;
                    visited[k][j] = true;
                    q.push({k, j, dist+1});
                }
            } else {
                col_reached[j] = i;
                for (int k = max(col_visited[j]+1, i+1); k <= i_limit; k++) {
                    if (k == m-1 && j == n-1) res = min(res, dist+1);
                    if (visited[k][j]) continue;
                    visited[k][j] = true;
                    q.push({k, j, dist+1});
                }
                col_visited[j] = max(col_visited[j], i_limit);
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};
