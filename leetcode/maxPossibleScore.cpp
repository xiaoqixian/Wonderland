// Date:   Sun Sep 08 10:55:49 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <algorithm>
#include <vector>
using std::vector;

#include <iostream>
auto init_ = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    return 0;
}();

// use binary search
class Solution {
public:
    int maxPossibleScore(vector<int>& start, const int d) {
        const int n = start.size();
        std::sort(start.begin(), start.end());
        // the theoritical max value is the min gap between sorted 
        // start numbers + d.
        int min_gap = start[1] - start[0];
        for (int i = 2; i < n; i++) {
            min_gap = std::min(min_gap, start[i] - start[i-1]);
        }

        // if it's possible that the min distance is greater than k.
        auto possible = [&start, n, d](const int k) {
            long long ss = 0;
            for (int i = 0; i < n-1; i++) {
                const long long base = std::max(ss, (long long)start[i]);
                ss = base + k;
                if (ss > (long long)start[i+1] + d) 
                    return false;
            }
            return true;
        };

        int l = 0, r = min_gap + d;
        int ret;
        printf("r = %d\n", r);
        while (l <= r) {
            const int m = l + (r-l)/2;
            if (possible(m)) {
                ret = m;
                l = m+1;
            } else {
                r = m-1;
            }
        }
        return ret;
    }
};

int main() {
    vector<int> start = {2,6,13,13};
    printf("%d\n", Solution().maxPossibleScore(start, 5));
}
