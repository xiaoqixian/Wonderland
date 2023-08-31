/**********************************************
  > File Name		: getSubarrayBeauty.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Apr 23 16:47:36 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, const int k, const int x) {
        const int n = nums.size();
        vector<int> res(n-k+1, 0);
        map<int, int> neg_freq;
        for (int i = 0; i < k; i++) {
            if (nums[i] >= 0) continue;
            const auto find = neg_freq.find(nums[i]);
            if (find == neg_freq.end())
                neg_freq.insert({nums[i], 1});
            else find->second++;
        }

        auto find_index = [&]() {
            int count = x;
            for (const auto [k, v]: neg_freq) {
                if (count <= v) return k;
                else count -= v;
            }
            return 0;
        };

        res[0] = find_index();

        for (int i = 0; i < n-k; i++) {
            neg_freq[nums[i]]--;
            if (nums[i+k] < 0) {
                const auto find = neg_freq.find(nums[i+k]);
                if (find == neg_freq.end())
                    neg_freq.insert({nums[i+k], 1});
                else find->second++;
            }

            res[i+1] = find_index();
        }

        return res;
    }
};
