/**********************************************
  > File Name		: divide.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 28 Jul 2021 10:22:34 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class Solution {
public:
    int divide(int dividend, int divisor) {
        return div(dividend, divisor);
    }

    int div(int a, int b) {
        if (a < b) return 0;
        int count = 1, tb = b;
        while ((b+b) <= a) {
            count += count;
            b += b;
        }

        return count + div(a - b, tb);
    }
};


int main() {
    Solution s;
    s.divide(10, 3);
}
