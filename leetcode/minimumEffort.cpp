/**********************************************
  > File Name		: minimumEffort.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 13 Feb 2022 09:32:27 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <algorithm>
#include "printv.h"
using namespace std;

/**
 * First consider how to determine the task that should be 
 * performed first in a bunch of tasks.
 */
bool cmp(vector<int>& i, vector<int>& k) {
    int d1 = i[1] - i[0], d2 = k[1] - k[0];
    if (d1 != d2)
        return d1 > d2;
    else
        return i[1] > k[1];
}

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int size = tasks.size();
        if (size == 1) return tasks[0][1];

        sort(tasks.begin(), tasks.end(), cmp);

        int res = tasks[0][1] - tasks[0][0];
        for (vector<int>& t: tasks) {
            res += t[0];
        }
        printf("max = %d\n", res);

        int remain = res, temp, val = res;
        for (vector<int>& t: tasks) {
            temp = val - t[1];
            val -= t[0];
            printf("remain = %d\n", temp);
            if (temp < remain)
                remain = temp;
        }
        printf("remain = %d\n", remain);
        return res - remain;
    }
};

int main() {
    vector<vector<int>> tasks = {{1,7},{2,8},{3,9},{4,10},{5,11},{6,12}};
    printf("%d\n", Solution().minimumEffort(tasks));
}
