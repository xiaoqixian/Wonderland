// Date:   Sun Sep 08 11:41:41 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector>
using std::vector;

// Weekly Contest 414
// Leetcode 3282
class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        const int n = nums.size();
        int i = 0;
        long long score = 0;
        
        for (int j = 1; j < n; j++) {
            if (nums[j] > nums[i]) {
                score += (long long)nums[i] * (j - i);
                i = j;
            }
        }

        return score + (long long)nums[i] * (n-1-i);
    }
};
