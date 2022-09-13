/**********************************************
  > File Name		: minGroups.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep 11 10:47:17 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> pq;
        for (auto &vec : intervals) {
            if (!pq.empty() && pq.top() < vec[0]) pq.pop();
            pq.push(vec[1]);
        }
        return pq.size();
    }
};

int main() {
    vector<vector<int>> intervals = {{5,10},{6,8},{1,5},{2,3},{1,10}};
    printf("%d\n", Solution().minGroups(intervals));
}
