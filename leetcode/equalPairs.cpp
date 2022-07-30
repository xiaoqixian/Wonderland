/**********************************************
  > File Name		: equalPairs.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Jul 29 20:15:52 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    int equalPairs(const vector<vector<int>>& grid) {
        int res = 0;
        const int n = grid.size();
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                res += compare(grid, i, k);
            }
        }
        return res;
    }

    int compare(const vector<vector<int>>& grid, int row, int col) {
        const int n = grid.size();
        const auto& v = grid[row];
        for (int i = 0; i < n; i++) {
            if (v[i] != grid[i][col])
                return 0;
        }
        return 1;
    }
};
