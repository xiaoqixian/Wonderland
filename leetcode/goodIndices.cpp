/**********************************************
  > File Name		: goodIndices.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep 25 11:17:13 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> goodIndices(const vector<int>& nums, const int k) {
        vector<int> res;
        const int n = nums.size();
        int step = 1;
        
        vector<bool> ascent(n, true), descent(n, true);
        for (int i = 1; i < k; i++) {
            if (nums[i] <= nums[i-1]) {
                ascent[0] = false;
                break;
            }
        }
        
        for (int i = k; i < n-k; i++) {
            
        }
    }
};
