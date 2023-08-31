// Date: Sun Aug 06 12:18:32 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

/*
 * Leetcode 6951
 * First let max path safeness be v
 * Try eliminate all cubes with safeness smaller than v.
 * If (0, 0) and (n-1, n-1) is still connected,
 * we can try to increase v, otherwise v should be decreased.
 *
 * To save time, we can binary search v between [0, n-1].
 */

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        const int n = grid.size();
        vector<vector<int>> cube(n, vector<int>(n, 0));
        vector<pair<int, int>> thieves;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j])
                    thieves.push_back({i, j});
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int safe = n<<1;
                for (auto const& p: thieves) {
                    safe = min(safe, abs(i - p.first) + abs(j - p.second));
                }
                cube[i][j] = safe;
            }
        }

        int l = 0, mid, r = n-1;

        //std::function<bool(int, int)> dfs = [&](int i, int j) {
            //if (cube[i][j] < mid) return false;
            //if (i == n-1 && j == n-1) return true;

            //visited[i][j] = true;
            //bool forward_res = ((i > 0 && !visited[i-1][j]) ? dfs(i-1, j) : false) ||
                //((i < n-1 && !visited[i+1][j]) ? dfs(i+1, j) : false) ||
                //((j > 0 && !visited[i][j-1]) ? dfs(i, j-1) : false) ||
                //((j < n-1 && !visited[i][j+1]) ? dfs(i, j+1) : false);

            //visited[i][j] = false;
            //return forward_res;
        //};

        queue<pair<int, int>> q;
        std::function<bool(int)> bfs = [&](int limit) {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            q.push({0, 0});
            while (!q.empty()) {
                auto const [i, j] = q.front();
                q.pop();
                if (cube[i][j] < limit) continue;
                
                visited[i][j] = true;

                if (i > 0 && !visited[i-1][j]) q.push({i-1, j});
                if (i < n-1 && !visited[i+1][j]) q.push({i+1, j});
                if (j > 0 && !visited[i][j-1]) q.push({i, j-1});
                if (j < n-1 && !visited[i][j+1]) q.push({i, j+1});
            }
            return visited[n-1][n-1];
        };

        int res = 0;
        while (l <= r) {
            mid = (l+r)/2;
            if (bfs(mid)) {
                res = mid;
                l = mid+1;
            }
            else r = mid-1;
        }
        return res;
    }
};

int main() {
    vector<vector<int>> grid = {{1,0,0},{0,0,0},{0,0,1}};
    cout << Solution().maximumSafenessFactor(grid) << endl;
}
