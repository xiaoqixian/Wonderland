/**********************************************
  > File Name		: minimumTime.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Apr 10 11:17:45 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
using namespace std;

class Solution {
public:
    long long minimumTime(vector<int>& time, const int totalTrips) {
        sort(time.begin(), time.end());
        const int n = time.size();
        long long left = 1, mid, right = (long long)totalTrips*time[0], sum;

        while (left <= right) {
            mid = (left + right)/2;
            sum = 0;
            for_each(time.cbegin(), time.cend(), 
                    [&](const int& t) {sum += mid/t;});
            if (sum >= totalTrips)
                right = mid - 1;
            else left = mid + 1;
        }
        sum = 0;
        for_each(time.cbegin(), time.cend(), 
                [&](const int& t) {sum += mid/t;});
        if (sum < totalTrips) return mid+1;
        return mid;
    }
};

