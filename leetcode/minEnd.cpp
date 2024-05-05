// Date:   Sun Apr 28 11:40:10 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

class Solution {
public:
    long long minEnd(int n, int x) {
        n--;
        auto res = 0ll;
        int xi = 0, ni = 0, ri = 0;
        for (; n > 0 || x > 0; ++ri) {
            if (x & 1) {
                res |= 1ll << ri;
            } else {
                res |= (long long)(n & 1) << ri;
                n >>= 1;
            }
            x >>= 1;
        }
        return res;
    }
};
