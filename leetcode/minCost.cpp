/**********************************************
  > File Name		: minCost.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Feb  5 17:07:23 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        std::unordered_map<int, int> count1, count2;
        const int n = basket2.size();
        auto set_or_add = [](std::unordered_map<int, int>& um, int k) {
            if (um.find(k) == um.end()) um[k] = 1;
            else um[k]++;
        };

        for (int i = 0; i < n; i++) {
            set_or_add(count1, basket1[i]);
            count2[basket1[i]] = 0;

            set_or_add(count2, basket2[i]);
            count1[basket2[i]] = 0;
        }

        for (const auto [k, v]: count1) {
            if ((v + count2[k]) % 2) return -1;
        }
    }
};
