/**********************************************
  > File Name		: trap.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Jul  5 13:37:02 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        const int size = height.size();
        vector<int> left(size), right(size);

        int highest = -1;
        for (int i = 0; i < size; i++) {
            const int h = height[i];

            if (h > highest) {
                left[i] = h;
                highest = h;
            } else {
                left[i] = highest;
            }
        }

        highest = -1;
        for (int i = size-1; i >= 0; i--) {
            const int h = height[i];

            if (h > highest) {
                right[i] = h;
                highest = h;
            } else {
                right[i] = highest;
            }
        }

        int res = 0;
        for (int i = 0; i < size; i++) {
            res += min(left[i], right[i]) - height[i];
        }
        return res;
    }
};
