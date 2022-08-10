/**********************************************
  > File Name		: countSubarrays.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug 10 20:51:42 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
using namespace std;

class Solution {
public:
    long long countSubarrays(const vector<int>& nums, const long long k) {
        long long res = 0;

        long long sum = nums[0]; int len = 1;
        const int n = nums.size();

        int start = 0, end = 1;
        while (start < n) {
            if (sum * len < k) {
                while (end < n && sum * len < k) {
                    sum += nums[end];
                    end++;
                    len++;
                }
                if (sum * len >= k) {
                    sum -= nums[--end];
                    len--;
                }
            } else {
                while (end > start && sum * len >= k) {
                    end--;
                    sum -= nums[end];
                    len--;
                }
                if (start == end) end++;
            }

            res += len;
            start++;
            if (start < n && start == end) {
                sum = nums[end++];
                len = 1;
            } else {
                sum -= nums[start-1];
                len--;
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {9,5,3,8,4,7,2,7,4,5,4,9,1,4,8,10,8,10,4,7};
    const int k = 4;
    printf("%lld\n", Solution().countSubarrays(nums, k));
}
