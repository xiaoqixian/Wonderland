/********************************************
 > File Name       : sumImbalanceNumbers.cpp
 > Author          : lunar
 > Email           : lunar_ubuntu@qq.com
 > Created Time    : Sun Jul  2 13:53:46 2023
 > Copyright@ https://github.com/xiaoqixian
********************************************/

#include <set>
#include <vector>
using namespace std;

class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        const int n = nums.size();
        multiset<int> sarr;
        int res = 0;
        for (int i = 0; i < n; i++) {
            sarr.insert(nums[i]);
            int imb = 0;
            for (int j = i+1; j < n; j++) {
                const int val = nums[j];
                auto it = sarr.insert(val);
                if (it == sarr.begin()) {
                    it++;
                    if (*it - val > 1)
                        imb++;
                } else if (it == --sarr.end()) {
                        it--;
                        if (val - *it > 1)
                            imb++;
                } else {
                    auto before = --it;
                    it++;
                    auto after = ++it;
                    if (*after - *before > 1) {
                        imb--;
                        if (val - *before > 1) imb++;
                        if (*after - val > 1) imb++;
                    }
                }
                res += imb;
            }
            sarr.clear();
        }
        return res;
    }
};
