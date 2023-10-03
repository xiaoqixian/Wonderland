// Date: Sun Sep 10 10:47:16 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

class Solution {
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        const int x_diff = abs(sx - fx), y_diff = abs(sy - fy);
        if (x_diff > t || y_diff > t) return false;
    }
};
