/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Jan 2022 10:26:31 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    bool sumOfNumberAndReverse(const int num) {
        if (!num) return true;
        auto inverse_digit = [](int num) {
            queue<int> q;
            while (num) {
                q.push(num % 10);
                num /= 10;
            }
            int res = 0;
            while (!q.empty()) {
                res *= 10;
                res += q.front();
                q.pop();
            }
            return res;
        };
        
        int digits = 1, div = 10;
        while (num / div) {
            digits++;
            div *= 10;
        }
        
        vector<bool> did(div, false);
        //div /= 10;
        //printf("div = %d\n", div);
        for (int i = 0; i < num; i++) {
            printf("i = %d\n", i);
            if (did[i]) continue;
            int inv_i = inverse_digit(i);
            if (inv_i + i == num) return true;
            did[inv_i] = true;
        }
        return false;
    }
};

int main() {
    if ((5-2 <= 3))
        printf("%d\n", Solution().sumOfNumberAndReverse(10));
}
