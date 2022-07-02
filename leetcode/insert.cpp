/**********************************************
  > File Name		: insert.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul  2 10:48:08 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
using namespace std;

class Solution {
public:
    static vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            intervals.push_back(newInterval);
            return intervals;
        }

        if (newInterval[1] < intervals[0][0]) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }

        int l = 0, r = intervals.size(), mid;

        while (l < r) {
            mid = (l + r) >> 1;
            
            if (intervals[mid][0] == newInterval[0])
                break;
            else if (intervals[mid][0] < newInterval[0]) {
                if (mid == intervals.size()-1 || intervals[mid+1][0] > newInterval[0])
                    break;
                else
                    l = mid;
            } else
                r = mid;
        }

        printf("mid = %d\n", mid);

        if (intervals[mid][1] < newInterval[0]) {
            if (mid == intervals.size()-1) {
                intervals.push_back(newInterval);
                return intervals;
            } else {
                mid++;
            }
        }
        
        l = intervals[mid][0] < newInterval[0] ? intervals[mid][0] : newInterval[0];

        auto start = intervals.begin() + mid, end = start;
        printf("start at %d\n", start->at(0));

        if (newInterval[1] < start->at(0)) {
            intervals.insert(start, newInterval);
            return intervals;
        }

        do {end++;} while (end != intervals.end() && end->at(0) <= newInterval[1]);

        end--;
        printf("end at %d\n", end->at(0));
        r = newInterval[1] > end->at(1) ? newInterval[1] : end->at(1);

        intervals.erase(start, ++end);
        //printf("end at %d\n", end->at(0));
        intervals.insert(start, {l, r});
        
        return intervals;
    }

    static void printv2(vector<vector<int>>& v2) {
        for (auto& v: v2)
            printf("[%d, %d], ", v[0], v[1]);
        printf("\n");
    }
};

int main() {
    vector<vector<int>> intervals = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    vector<int> newInterval = {4, 8};
    auto res = Solution::insert(intervals, newInterval);

    Solution::printv2(res);
}
