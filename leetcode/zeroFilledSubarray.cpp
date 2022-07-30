/**********************************************
  > File Name		: zeroFilledSubarray.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 30 15:10:59 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        const int n = nums.size();
        int i = 0, zero_num = 0;
        bool flag = false;
        vector<int> consec_zeros;
        while (i < n) {
            switch (nums[i]) {
                case 0:
                    zero_num++;
                    flag = true;
                    break;
                default:
                    if (flag) {
                        consec_zeros.push_back(zero_num);
                        zero_num = 0;
                        flag = false;
                    }
            }
            i++;
        }

        long long res = 0;
        for (int n: consec_zeros) {
            res += (n*(n+1))>>1;
        }
        return res;
    }
};
