/**********************************************
  > File Name		: wayToMakeFair.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 12 Feb 2022 05:17:01 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include "printv.h"
using namespace std;

class Solution {
public:
    static int waysToMakeFair(vector<int>& nums) {
        int size = nums.size(), res = 0;
        vector<int> accu(size+2, 0);
        int even_sum = 0, odd_sum = 0;
        int even_last = size % 2 == 0 ? size : size+1;
        int odd_last = size % 2 == 0 ? size+1 : size;
        
        for (int i = 0; i < size-1; i += 2) {
            accu[i+2] = accu[i] + nums[i];
            accu[i+3] = accu[i+1] + nums[i+1];
        }

        if (size % 2) {
            accu[size+1] = accu[size-1] + nums[size-1];
        }

        printv(accu);
        
        for (int i = 2; i < size+1; i += 2) {
            even_sum = accu[i-2] + accu[odd_last] - accu[i-1];
            odd_sum = accu[i-1] + accu[even_last] - accu[i];
            if (even_sum == odd_sum) res++;

            even_sum = accu[i] + accu[odd_last] - accu[i+1];
            odd_sum = accu[i-1] + accu[even_last] - accu[i];
            if (even_sum == odd_sum) res++;
        }

        if (size % 2) {
            int i = size-1;
            even_sum = accu[i-2] + accu[odd_last] - accu[i-1];
            odd_sum = accu[i-1] + accu[even_last] - accu[i];
            if (even_sum == odd_sum) res++;
        }

        return res;
    }
};

int main() {
    vector<int> nums = {1,1,1,1,1};
    printf("%d\n", Solution::wayToMakeFair(nums));
}
