/**********************************************
  > File Name		: combinationSum.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 30 Jul 2021 11:18:13 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        
        vector<int> curr;
        reverse(candidates, target, res, curr, 0, 0);
        return res;
    }

    bool reverse(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& curr, int index, int sum) {
        for (int i = index; i < candidates.size(); i++) {
            int c = candidates[i];
            if (c + sum > target) {
                return false;
            }
            else if (c + sum == target) {
                curr.push_back(c);
                res.push_back(vector<int>(curr));
                curr.pop_back();
                return true;
            }
            else {
                curr.push_back(c);
                reverse(candidates, target, res, curr, i, sum+c);
                curr.pop_back();
            }
        }
        return false;
    }

    void printv3(const vector<vector<vector<int>>>& v) {
        printf("[");
        printv2(v[0]);
        for (int i = 1; i < v.size(); i++) {
            printf("\n");
            printv2(v[i]);
        }
        printf("]\n");
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
    vector<int> v = {2,3,5};
    vector<vector<int>> res = s.combinationSum(v, 8);
    s.printv2(res);
}
