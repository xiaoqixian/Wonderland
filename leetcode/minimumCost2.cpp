/********************************************
 > File Name       : minimumCost2.cpp
 > Author          : lunar
 > Email           : lunar_ubuntu@qq.com
 > Created Time    : Sun May 28 12:17:55 2023
 > Copyright@ https://github.com/xiaoqixian
********************************************/

#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    long long minimumCost(string& num) {
        const int n = num.size(), half = n/2;
        long long res = 0;
        for (int i = half-1; i; i--) {
            if (num[i] != num[i-1]) {
                res += i;
            }
        }
        for (int i = half; i < n-1; i++) {
            if (num[i] != num[i+1]) {
                res += n-i;
            }
        }
        if (num[half-1] != num[half])
            res += half;
        return res;
    }
};
