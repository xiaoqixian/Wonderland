/**********************************************
  > File Name		: combinationSum3.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 09 Dec 2021 02:33:43 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> curr;
        reverse(k, n, res, curr, 1, 0);
        return res;
    }

    void reverse(int k, int n, vector<vector<int>>& res, vector<int>& curr, int index, int sum) {
        if (k == 0) {
            return;
        }
        for (int i = index; i < 10; i++) {
            if (i + sum > n) {
                return;
            } else if (i + sum == n) {
                if (k == 1) {
                    curr.push_back(i);
                    res.push_back(vector<int>(curr));
                    curr.pop_back();
                } else {
                    return;
                }
            } else {
                curr.push_back(i);
                reverse(k-1, n, res, curr, i+1, sum+i);
                curr.pop_back();
            }
        }
    } 

    void printv2(vector<vector<int>> v) {
        printf("[");
        printv1(v[0]);
        for (int i = 1; i < v.size(); i++) {
            auto vv = v[i];
            printf(", ");
            printv1(vv);
        }
        printf("]\n");
    }

    void printv1(vector<int> v) {
        printf("[%d", v[0]);
        for (int i = 1; i < v.size(); i++) {
            printf(", %d", v[i]);
        }
        printf("]");
    }
};


int main() {
    Solution s;
    auto res = s.combinationSum3(3, 7);
    s.printv2(res);
}
