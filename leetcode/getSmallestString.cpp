/**********************************************
  > File Name		: getSmallestString.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 12 Feb 2022 04:19:58 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

/**
 * Insanely easy
 */
class Solution {
public:
    static string getSmallestString(int n, int k) {
        string res(n, 'a');
        k -= n;
        int index = n, dec;

        while (k && index) {
            dec = min(k, 25);
            printf("dec = %d\n", dec);
            k -= dec;
            res[--index] += dec;
        }
        return res;
    }
};

int main() {
    cout << Solution::getSmallestString(5, 73) << endl;
}
