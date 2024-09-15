// Date:   Sun Sep 15 10:35:43 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector>
using std::vector;

// Leetcode weekly contest 415
class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        const int n = b.size();
        vector<vector<long long>> dp(4, vector<long long>(n));
        dp[0][0] = (long long)a[0] * b[0];
        auto& dp0 = dp[0];
        for (int j = 1; j < n; j++) {
            dp0[j] = std::max(dp0[j-1], (long long)a[0] * b[j]);
        }

        for (int i = 1; i < 4; i++) {
            auto& dpi = dp[i];
            const long long ai = a[i];
            dpi[i] = dp[i-1][i-1] + ai * b[i];
            for (int j = i+1; j < n; j++) {
                dpi[j] = std::max(dpi[j-1], ai * b[j] + dp[i-1][j-1]);
            }
        }

        return dp[3][n-1];
    }
};
