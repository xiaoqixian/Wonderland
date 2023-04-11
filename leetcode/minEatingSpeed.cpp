/**********************************************
  > File Name		: minEatingSpeed.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Apr  9 22:11:30 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        sort(piles.begin(), piles.end());
        const int n = piles.size();
        int left = 1, mid, right = piles[n-1];
        int test = 50;
        while (left <= right) {
            mid = (left + right)/2;
            //printf("left = %d, mid = %d, right = %d\n",left, mid, right);
            long long count = 0;
            for_each(piles.cbegin(), piles.cend(), 
                    [&](const int& k) {count += k/mid + ((k%mid) ? 1 : 0);});
            //count<=h 说明以mid的速度吃还比较快，可以考虑减慢;否则应该加快
            if (count <= h) right = mid-1;
            else left = mid+1;
        }
        int count = 0;
        for_each(piles.cbegin(), piles.cend(), 
                [&](const int& k) {count += k/mid + ((k%mid) ? 1 : 0);});
        if (count <= h) return mid;
        else return mid+1;
    }
};
