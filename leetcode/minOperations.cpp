/**********************************************
  > File Name		: minOperations.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 04 Feb 2022 02:26:44 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int left = -1, right = nums.size() - 1;
        int res = nums.size() + 1;

        int left_cost = 0, right_cost = 0;
        int op = 0, sum;
        while (1) {
            sum = x;
            sum -= left_cost;

            printf("\nsum = %d\n", sum);

            if (sum <= 0) {
                if (!sum && res > op - nums.size() + 1 + right)
                    res = op - nums.size() + 1 + right;
                break;
            }

            if (sum == right_cost) {
                if (res > op)
                    res = op;
                printf("exactly\n");
            } else if (sum < right_cost) {
                while (right_cost && sum < right_cost) {
                    printf("right = %d, right_cost = %d\n", right, right_cost);
                    right_cost -= nums[++right];
                    op--;
                }

                printf("go right, right_cost = %d\n", right_cost);
                if (sum == right_cost && res > op)
                    res = op;
            } else {
                while (right > left && sum > right_cost) {
                    right_cost += nums[right--];
                    op++;
                }

                printf("go left, right_cost = %d\n", right_cost);
                if (sum == right_cost && res > op)
                    res = op;
                if (right == left && right_cost < sum)
                    goto result;
            }
            left_cost += nums[++left];
            op++;
        }

result:
        if (res == nums.size() + 1) 
            return -1;
        else
            return res;
    }
};

//or use slide window
//omitted

int main() {
    vector<int> nums = {500, 1, 4, 3};
    int x = 500;
    Solution s;
    printf("%d\n", s.minOperations(nums, x));
}
