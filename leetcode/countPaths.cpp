/**********************************************
  > File Name		: countPaths.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug  3 21:25:40 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stdexcept>
#include <vector>
using namespace std;

/*
 * 
 */
class Solution {
private:
    static const int mod = 1e9 + 7;
    int m, n, res;
    vector<vector<bool>> appear, add_started;
    vector<pair<int, int>> start;
    vector<vector<int>> paths;
public:
    int countPaths(const vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size(), res = 0; 

        start.push_back(make_pair(0, 0));
        appear = vector<vector<bool>>(m, vector<bool>(n, false));
        add_started = vector<vector<bool>>(m, vector<bool>(n, false));
        paths = vector<vector<int>>(m, vector<int>(n, 0));

        add_started[0][0] = true;

        while (!start.empty()) {
            auto cord = start.back(); start.pop_back();
            if (appear[cord.first][cord.second]) continue;
            explore(grid, cord.first, cord.second, 0);
        }
        return res;
    }
    
    int explore(const vector<vector<int>>& grid, int x, int y, int len) {
        if (appear[x][y]) 
            return paths[x][y];
        else len++;
        appear[x][y] = true;

        auto go_next = [&](int x, int y, int new_x, int new_y) {
            if (grid[x][y] < grid[new_x][new_y])
                return explore(grid, new_x, new_y, len);
            else {
                if (!appear[new_x][new_y] && !add_started[new_x][new_y]) {
                    start.push_back(make_pair(new_x, new_y));
                    add_started[new_x][new_y] = true;
                }
                return 0;
            }
        };

        int temp_res = 0;

#define GO_OR_BACK(x, y, new_x, new_y)\
        if (grid[x][y] < grid[new_x][new_y])\
            explore(grid, new_x, new_y, len);\
        else {\
            if (!appear[new_x][new_y] && !add_started[new_x][new_y]) {\
                start.push_back(make_pair(new_x, new_y));\
                add_started[new_x][new_y] = true;\
                printf("(%d, %d) push new start(%d, %d)\n", x, y, new_x, new_y);\
            }\
        }
        //go right
        if (y < n-1) {
            temp_res += go_next(x, y, x, y+1);
            temp_res %= mod;
        }

        //go left
        if (y > 0) {
            temp_res += go_next(x, y, x, y-1);
            temp_res %= mod;
        }

        //go down
        if (x < m-1) {
            temp_res += go_next(x, y, x+1, y);
            temp_res %= mod;
        }

        //go up
        if (x > 0) {
            temp_res += go_next(x, y, x-1, y);
            temp_res %= mod;
        }
        
        paths[x][y] = temp_res+1;
        res += paths[x][y];
        res %= mod;
        return temp_res + 1;
    }
};
