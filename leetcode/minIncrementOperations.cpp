// Date: Sun Oct 29 12:19:41 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector> 

class Solution {
public:
    long long minIncrementOperations(
            std::vector<int>& nums, const int k) {
        const int n = nums.size();
        long long res = 0;
        // let dp[i] be the minimum increment operations
        // required to make the first i values beautiful
        // while also having the value dp[i] >= k.
        std::vector<long long> dp(n, 0);

        dp[0] = std::max(0, k - nums[0]);
        dp[1] = std::max(0, k - nums[1]);
        dp[2] = std::max(0, k - nums[2]);

        for (int i = 3; i < n; i++) {
            dp[i] = (long long)std::max(0, k - nums[i]) +
                std::min({dp[i-3], dp[i-2], dp[i-1]});
        }

        return std::min({dp[n-3], dp[n-2], dp[n-1]});
    }
};
