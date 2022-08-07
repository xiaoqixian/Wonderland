/**********************************************
  > File Name		: validPartition.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug  7 11:12:55 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_set>
using namespace std;

/*
 * 需要一个unordered_set来缓存失败的position，避免超时
 */
class Solution {
private:
    unordered_set<int> cache;
public:
    bool validPartition(vector<int>& nums) {
        return _validPartition(nums, 0);
    }

    bool _validPartition(const vector<int>& nums, const int start) {
        const int n = nums.size();
        if (start == n) return true;
        if (start == n-1 || this->cache.count(start))
            return false;

        if (start+2 <= n) {
            if (nums[start] == nums[start+1] && _validPartition(nums, start+2))
                return true;
        }

        if (start+3 <= n) {
            const int l = nums[start], m = nums[start+1], r = nums[start+2];
            bool check = ((m - l == 1 && r - m == 1) || (l == m && m == r));
            if (check && _validPartition(nums, start+3))
                return true;
        }

        this->cache.insert(start);

        return false;
    }


};

