/**********************************************
  > File Name		: getLastMoment.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Aug 2020 11:27:21 PM CST
 **********************************************/

#include <iostream>
using namespace std;

/*
 Leetcode 1503.所有蚂蚁掉下来的那一刻
 差点被这道题迷惑了，由于不区分具体的蚂蚁，所以根本不需要看什么两个蚂蚁相遇就会调头。
 两只蚂蚁相遇后调头和相遇后直接擦身而过的效果是一样的。
 这样就只要看最远的那只蚂蚁走的路程。
 */

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int leftMax = 0, rightMax = n;
        for (int i = 0; i < left.size(); i++) {
            if (left[i] > leftMax) {
                leftMax = left[i];
            }
        }
        for (int i = 0; i < right.size(); i++) {
            if (right[i] < rightMax) {
                rightMax = right[i];
            }
        }
        int maxlen = leftMax > n - rightMax ? leftMax : n-rightMax;
        return maxlen;
    }
};
