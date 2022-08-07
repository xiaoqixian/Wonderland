/**********************************************
  > File Name		: maximumSplicedArray.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Aug  5 23:39:55 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        const int n = nums1.size();
        auto sum_op = [](const vector<int>& nums) {
            return std::accumulate(nums.begin(), nums.end(), 0, [](const int& acc, const int& num) {return acc + num;});
        };

        int sum1 = sum_op(nums1), sum2 = sum_op(nums2), b_sum, l_sum;
        vector<int> diff(n, 0);
        int prev = 0;

        auto set_diff = [&](const vector<int>& n1, const vector<int>& n2) {
            for (int i = 0; i < n; i++)
                diff[i] = n1[i] - n2[i];
        };
        if (sum1 < sum2) {
            set_diff(nums1, nums2);
            b_sum = sum2;
            l_sum = sum1;
        } else {
            set_diff(nums2, nums1);
            b_sum = sum1;
            l_sum = sum2;
        }

        int max_diff = 0, min_diff = 0;
        vector<int> dp(n, 0), dp_min(n, 0);
        dp[0] = diff[0];
        dp_min[0] = diff[0];

        for (int i = 1; i < n; i++) {
            dp[i] = max(diff[i], dp[i-1] + diff[i]);
            dp_min[i] = min(diff[i], dp_min[i-1] + diff[i]);
            if (dp[i] > max_diff)
                max_diff = dp[i];
            if (dp_min[i] < min_diff)
                min_diff = dp_min[i];
        }

        return max(b_sum + max_diff, l_sum - min_diff);
    }
};
