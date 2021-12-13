/**********************************************
  > File Name		: minSubarray.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 13 Dec 2021 10:12:41 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        int ans = n;
        long long sum = 0;
        unordered_map<int,int> cnt;
        
        for(int i = 0; i < n; ++i) sum += nums[i];
        int rest = sum%p;
        if(rest == 0) return 0;
        
        cnt[0] = 0;
        sum = 0;
        for(int i = 1; i <= n; ++i){
            sum += nums[i-1];
            int x = (sum - rest + p)%p;
            if(cnt.count(x)){
                ans = min(ans,i - cnt[x]);
            }
            cnt[sum%p] = i;
        }
        if(ans == n) return -1;
        return ans;
    }
};

int main() {
    Solution s;

    printf("%d\n", s.minSubarray(nums, 9709797321));
}
