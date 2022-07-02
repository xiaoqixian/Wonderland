/**********************************************
  > File Name		: combinationSum2.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 09 Dec 2021 12:18:43 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        map<int, int> m;
        vector<int> can;
        int count, num = -1;
        for (int c: candidates) {
            if (c != num) {
                if (num != -1) {
                    m[num] = count;
                }
                count = 1;
                num = c;
                can.push_back(c);
            } else {
                count++;
            }
        }
        m[num] = count;

        this->printm(m);
        
        vector<vector<int>> res;
        vector<int> curr;
        reverse(can, target, res, curr, 0, 0, m);
        return res;
    }

    void reverse(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& curr, int index, int sum, map<int, int>& m) {
        for (int i = index; i < candidates.size(); i++) {
            int c = candidates[i];
            if (m[c] <= 0) {
                continue;
            }
            if (c + sum > target) {
                return;
            } else if (c + sum == target) {
                curr.push_back(c);
                res.push_back(vector<int>(curr));
                curr.pop_back();
                return;
            } else {
                curr.push_back(c);
                m[c]--;
                this->reverse(candidates, target, res, curr, i, sum+c, m);
                curr.pop_back();
                m[c]++;
            }
        }
    }

    void printv2(vector<vector<int>>& v) {
        printf("[");
        printv1(v[0]);
        for (int i = 1; i < v.size(); i++) {
            auto vv = v[i];
            printf(", ");
            printv1(vv);
        }
        printf("]\n");
    }

    void printv1(vector<int>& v) {
        printf("[%d", v[0]);
        for (int i = 1; i < v.size(); i++) {
            printf(", %d", v[i]);
        }
        printf("]");
    }

    void printm(map<int, int>& m) {
        printf("{");
        auto iter = m.begin();
        printf("[%d, %d]", iter->first, iter->second);
        iter++;
        while (iter != m.end()) {
            printf(", [%d, %d]", iter->first, iter->second);
            iter++;
        }
        printf("}\n");
    }
};

int main() {
    //vector<int> candidates = {10,1,2,7,6,1,5};
    vector<int> candidates = {2,5,2,1,2};
    Solution s;
    vector<vector<int>> res = s.combinationSum2(candidates, 5);
    s.printv2(res);
}
