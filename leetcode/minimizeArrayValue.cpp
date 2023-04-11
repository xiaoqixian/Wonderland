/**********************************************
  > File Name		: minimizeArrayValue.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Apr 10 20:42:37 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int minimizeArrayValue(const vector<int>& nums) {
        const int n = nums.size();
        int left, mid, right = 0;
        long long sum = 0, debt;
        for (const int num: nums) {
            sum += num;
            if (right < num) right = num;
        }
        left = ceil(sum / n);

        while (left <= right) {
            mid = (left + right)/2;
            debt = 0;
            for (int i = n-1; i; i--) {
                debt += nums[i] - mid;
                if (debt < 0) debt = 0;
            }
            debt += nums[0] - mid;
            if (debt > 0) left = mid+1;
            else right = mid-1;
        }
        if (debt > 0) return mid+1;
        return mid;
    }
};
