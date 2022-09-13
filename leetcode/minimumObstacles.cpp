/**********************************************
  > File Name		: minimumObstacles.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Aug 15 23:27:55 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
private:
    int res;
public:
    int minimumObstacles(const vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();
        this->res = 0;
        vector<vector<bool>> visit(m, vector<bool>(n, false));

        std::function<void(int, int, int)> go;

        std::function<void(int, int, int)> trace = [&](int x, int y, int len) {
            if (x == m-1 && y == n-1) {
                if (len < this->res)
                    this->res = len;
                return;
            }
            //go Left
            go(x-1, y, len);

            //go Right
            go(x+1, y, len);

            //go Down
            go(x, y+1, len);

            //go Up
            go(x, y-1, len);
        };

        go = [&](int x, int y, int len) {
            if ((x >= 0 && x < m) && (y >= 0 && y < n) && !visit[x][y]) {
                len += grid[x][y];
                visit[x][y] = true;
                if (len < this->res)
                    trace(x, y, len);
                visit[x][y] = false;
            }
        };

        trace(0, 0, 0);
        return this->res;
    }
};
