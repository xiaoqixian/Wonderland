/**********************************************
  > File Name		: minOperations2.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Apr 24 16:12:54 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

//leetcode 2654

#include <vector>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        auto gcd = [](int a, int b) {
            while (true) {
                if (a > b) a -= b;
                else if (a < b) b -= a;
                else return a;
            }
        };


    }
};
