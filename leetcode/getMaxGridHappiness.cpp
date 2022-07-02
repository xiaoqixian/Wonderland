/**********************************************
  > File Name		: getMaxGridHappiness.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 04 Feb 2022 05:38:44 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class Solution {
private:
    // 预处理：每一个 mask 的三进制表示
    int mask_span[729][6];
    // dp[上一行的 mask][当前处理到的行][剩余的内向人数][剩余的外向人数]
    int dp[729][6][7][7];
    // 预处理：每一个 mask 包含的内向人数，外向人数，行内得分（只统计 mask 本身的得分，不包括它与上一行的），行外得分
    int nx_inner[729], wx_inner[729], score_inner[729], score_outer[729][729];
    // n3 = n^3
    int m, n, n3;
    
public:
    // 如果 x 和 y 相邻，需要加上的分数
    inline int calc(int x, int y) {
        if (x == 0 || y == 0) {
            return 0;
        }
        // 例如两个内向的人，每个人要 -30，一共 -60，下同
        if (x == 1 && y == 1) {
            return -60;
        }
        if (x == 2 && y == 2) {
            return 40;
        }
        return -10;
    }
    
    int getMaxGridHappiness(int m, int n, int nx, int wx) {
        this->m = m;
        this->n = n;
        this->n3 = pow(3, n);
        
        // 预处理
        for (int mask = 0; mask < n3; ++mask) {
            for (int mask_tmp = mask, i = 0; i < n; ++i) {
                mask_span[mask][i] = mask_tmp % 3;
                mask_tmp /= 3;
            }
            nx_inner[mask] = wx_inner[mask] = score_inner[mask] = 0;
            for (int i = 0; i < n; ++i) {
                if (mask_span[mask][i] != 0) {
                    // 个人分数
                    if (mask_span[mask][i] == 1) {
                        ++nx_inner[mask];
                        score_inner[mask] += 120;
                    }
                    else if (mask_span[mask][i] == 2) {
                        ++wx_inner[mask];
                        score_inner[mask] += 40;
                    }
                    // 行内分数
                    if (i - 1 >= 0) {
                        score_inner[mask] += calc(mask_span[mask][i], mask_span[mask][i - 1]);
                    }
                }
            }
        }
        // 行外分数
        for (int mask0 = 0; mask0 < n3; ++mask0) {
            for (int mask1 = 0; mask1 < n3; ++mask1) {
                score_outer[mask0][mask1] = 0;
                for (int i = 0; i < n; ++i) {
                    score_outer[mask0][mask1] += calc(mask_span[mask0][i], mask_span[mask1][i]);
                }
            }
        }
        
        memset(dp, -1, sizeof(dp));
        return dfs(0, 0, nx, wx);
    }
    
    
    // dfs(上一行的 mask，当前处理到的行，剩余的内向人数，剩余的外向人数）
    int dfs(int mask_last, int row, int nx, int wx) {
        // 边界条件：如果已经处理完，或者没有人了
        if (row == m || nx + wx == 0) {
            return 0;
        }
        // 记忆化
        if (dp[mask_last][row][nx][wx] != -1) {
            return dp[mask_last][row][nx][wx];
        }
        
        int best = 0;
        for (int mask = 0; mask < n3; ++mask) {
            if (nx_inner[mask] > nx || wx_inner[mask] > wx) {
                continue;
            }
            int score = score_inner[mask] + score_outer[mask][mask_last];
            best = max(best, score + dfs(mask, row + 1, nx - nx_inner[mask], wx - wx_inner[mask]));
        }
        
        return dp[mask_last][row][nx][wx] = best;
    }
};

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int a, int b) {
        // 0- 不放人 1-放内向 2-放外向 3^n
        int cases = pow(3, n);
        int cases_1 = pow(3, n-1);
        int offset[3][3] = {0, 0, 0, 0, -60, -10, 0, -10, 40};
        
        int M = cases - 1;
        int dp[m*n + 1][a+1][b+1][cases];
        memset(dp, 0, sizeof(dp));
        
        for(int coor = m*n-1; coor >= 0; --coor) {
            int i = coor / n, j = coor % n;
            for(int x = 0; x <= a; ++x) {
                for(int y = 0; y <= b; ++y) {
                    for(int pre = 0; pre < cases; ++pre) { // pre 就是前 n 个格子的状态（三进制）
                        int nem = (pre * 3) % cases; // nem 是 pre “左移” 一位, 并去掉首位的状态,比如三进制 2121->三进制 1210.
                        if(x > 0) {
                            int diff = 120 + (j!=0)*offset[1][pre % 3] + offset[1][pre / cases_1];
                            dp[coor][x][y][pre] = max(dp[coor][x][y][pre], diff + dp[coor + 1][x-1][y][nem + 1]);
                        }
                        if(y > 0) {
                            int diff = 40 + (j!=0)*offset[2][pre % 3] + offset[2][pre / cases_1];
                            dp[coor][x][y][pre] = max(dp[coor][x][y][pre], diff + dp[coor + 1][x][y-1][nem + 2]);
                        }
                        dp[coor][x][y][pre] = max(dp[coor][x][y][pre], dp[coor + 1][x][y][nem]);
                    }
                }
            }
        }
        return dp[0][a][b][0];
    }
};

