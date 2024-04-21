// Date:   Sun Apr 21 10:53:00 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <utility>
#include <vector>
using std::vector;
using std::pair;

class Solution {
    pair<pair<int, int>, pair<int, int>> min_two(vector<int> const& v) {
        int mi = 0, me = INT_MAX;
        int smi = 0, sme = INT_MAX;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] < me) {
                smi = mi;
                sme = me;
                mi = i;
                me = v[i];
            } else if (v[i] < sme) {
                sme = v[i];
                smi = i;
            }
        }
        return {{mi, me}, {smi, sme}};
    }
public:
    int minimumOperations(vector<vector<int>>& grid) {
        const int n = grid[0].size(), m = grid.size();
        vector<vector<int>> dp(n);

        vector<int> fc(10, m);
        for (int r = 0; r < m; ++r) {
            fc[grid[r][0]]--;
        }
        auto [mp, smp] = min_two(fc);
        dp[0] = vector<int>(10, mp.second);
        dp[0][mp.first] = smp.second;

        int res = mp.second;
        for (int c = 1; c < n; ++c) {
            fc = vector<int>(10, m);
            for (int r = 0; r < m; ++r) {
                fc[grid[r][c]]--;
            }

            vector<int> opselect(10);
            for (int i = 0; i < 10; ++i) {
                opselect[i] = fc[i] + dp[c-1][i];
            }
            
            auto [mp, smp] = min_two(opselect);
            res = mp.second;
            
            vector<int> dpc(10, mp.second);
            dpc[mp.first] = smp.second;
            dp[c] = std::move(dpc);
        }
        return res;
    }
};
