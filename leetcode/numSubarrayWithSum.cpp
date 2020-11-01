/**********************************************
  > File Name		: numSubarrayWithSum.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 26 Oct 2020 11:49:23 PM CST
  > Location        : Shanghai
 **********************************************/

/*
 * Leetcode 930.和相同的二元子数组
 * 一个经典的子数组问题，只不过这次的数组是二元的
 * 可以从开头找到一个符合的子数组
 * 创建两个指针，一个指向子数组的开始，并且是1,另一个指向结束，也是1
 * 这两个指针以内的数组就是一个符合要求的子数组。
 */

class Solution {
public:
    int numSubarrayWithSum(vector<int>& A, int S) {
        int res = 0, len = A.size();
        int lp = 0, rp = 0;
        int temp = 0;
        while (temp < S) {

        }
    }
};
