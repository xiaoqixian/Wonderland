/**********************************************
  > File Name		: getPermutation.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul  2 23:02:07 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
private:
    int factorial[10];
public:
    Solution() {
        this->factorial[1] = 1;
        for (int i = 2; i < 10; i++) {
            this->factorial[i] = this->factorial[i-1] * i;
        }
    }

    string getPermutation(int n, int k) {
        k--;
        string res(n, ' ');
        vector<bool> take(n+1, false);

        for (int i = 1; i < n+1; i++) {
            int times = k / this->factorial[n-i];
            k %= this->factorial[n-i];
    
            int num = 1;
            while (take[num]) num++;
            while (times) {
                times--;
                num++;
                while (take[num]) num++;
            }
            take[num] = true;
            //printf("num = %d, take[%d] = %s\n\n", num, num, take[num] ? "true" : "false");
            res[i-1] = '0' + num;
        }

        return res;
    }
};

#include <iostream>
int main() {
    cout << Solution().getPermutation(4, 9) << endl;
}
