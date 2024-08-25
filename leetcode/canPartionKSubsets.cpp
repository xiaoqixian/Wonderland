// Date:   Sun Aug 25 16:13:03 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <functional>
#include <numeric>
#include <vector>
#include <stdint.h>
using std::vector;

class Solution {
public:
    bool canPartitionKSubsets(vector<int> const& nums, const int k) {
        const int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % k != 0) return false;
        const int div = sum / k;
        for (auto const num: nums) {
            if (num > div) return false;
        }

        // As the max size of nums is <= 16,
        // we can use a 16-bit number to represent the states of numbers,
        // dp[S] represents if it can work out when the state number is S.
        const int n = nums.size();
        vector<bool> dp(1 << n, true);

        // s is the state number
        // p is 
        std::function<bool(int, int)> dfs = [&](int s, int p) {
            if (s == 0) return true;

            // not a available state number
            if (!dp[s]) return false;
            // mark this state number as used
            dp[s] = false;
            
            for (int i = 0; i < n; i++) {
                if (nums[i] + p > div) break;

                if ((s >> i) & 1) {
                    if (dfs(s ^ (1 << i), (p + nums[i]) % div)) 
                        return true;
                }
            }
            return false;
        };

        return dfs((1 << n)-1, 0);
    }
};
