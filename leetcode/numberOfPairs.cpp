/**********************************************
  > File Name		: numberOfPairs.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul 17 19:27:44 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        vector<int> res = {0, 0};
        int& pairs = res[0];
        int& len = res[1];
        len = nums.size();

        unordered_map<int, int> m;

        for (const int i: nums) {
            auto it = m.find(i);

            if (it == m.end()) {
                m.insert({i, 1});
            } else {
                it->second += 1;
            }
        }

        for (auto const& [k, v]: m) {
            pairs += v / 2;
            len += v % 2;
        }

        return res;
    }
};
