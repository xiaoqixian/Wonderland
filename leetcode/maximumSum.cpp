/**********************************************
  > File Name		: maximumSum.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul 17 19:56:03 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
private:
    static int digitSum(int num) {
        int res = 0;
        while (num) {
            res += num % 10;
            num /= 10;
        }
        return res;
    }

public:
    int maximumSum(const vector<int>& nums) {
        unordered_map<int, pair<int, int>> um;
        
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int sum = digitSum(nums[i]);
            auto it = um.find(sum);

            if (it == um.end()) {
                um.insert({sum, {i, -1}});
            } else {
                int& f = it->second.first;
                int& s = it->second.second;

                if (s == -1) {
                    if (nums[i] > nums[f]) {
                        s = f;
                        f = i;
                    } else {
                        s = i;
                    }
                } else if (nums[i] > nums[s]) {
                    if (nums[i] > nums[f]) {
                        s = f;
                        f = i;
                    } else {
                        s = i;
                    }
                }

                res = max(res, nums[f] + nums[s]);
            }
        }

        return res;
    }
};
