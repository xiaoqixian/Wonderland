// Date:   Sun Sep 22 10:45:35 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <cstring>
#include <vector>
using std::vector;

// Leetcode weekly contest 416.2
class Solution {
public:
    int calcMaxHeight(long long time, int wt) {
        long long left = 0, right = sqrt(2 * time / wt) + 1;
        while (left < right) {
            long long mid = left + (right - left + 1) / 2;
            if (wt * mid * (mid + 1) / 2 <= time) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }

    bool canFinish(long long t, int mountainHeight, vector<int> const& workerTimes) {
        long long totalHeight = 0;
        for (int time : workerTimes) {
            totalHeight += calcMaxHeight(t, time);
            if (totalHeight >= mountainHeight) return true;
        }
        return totalHeight >= mountainHeight;
    }

    long long minNumberOfSeconds(const int mountainHeight, vector<int> const& workerTimes) {
        // use binary search
        long long left = 0, right = 1LL << 60;
        while (left < right) {
            const long long mid = left + (right - left) / 2;
            if (canFinish(mid, mountainHeight, workerTimes)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
