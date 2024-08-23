// Date:   Thu Aug 22 21:20:01 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <cstdio>
#include <vector>

// Leetcode 3133
class Solution {
public:
    long long minEnd(int n, const int x) {
        n--;
        long long res = x;
        int idx = 0;
        while (n) {
            while (idx < 32 && x & (1 << idx)) idx++;
            res |= (long long)(n & 1) << idx;
            n >>= 1;
            idx++;
        }
        
        return res;
    }
};

int main() {
    printf("%lld\n", Solution().minEnd(3, 4));
}
