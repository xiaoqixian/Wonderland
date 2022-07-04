/**********************************************
  > File Name		: largestRectangleArea.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul  2 21:33:53 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stack>
using namespace std;

/*
 * Monotonous Stack
 */
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int m = heights.size();

        vector<int> left(m, 0), right(m, 0);

        stack<int> s;
        for (int i = 0; i != m; i++) {
            while (!s.empty() && heights[s.top()] >= heights[i]) {
                right[s.top()] = i;
                s.pop();
            }

            left[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }

        int res = 0;
        for (int i = 0; i < m; i++) {
            int length = right[i] - left[i] - 1;
            int area = length * heights[i];
            res = max(res, area);
        }
        return res;
    }
};
