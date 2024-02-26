// Date:   Sun Feb 25 11:02:21 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector>
#include <iostream>
#include <functional>

template <typename T>
using vector = std::vector<T>;

template <typename T>
static void print(T const& item) {
    std::cout << item << std::endl;
}

class Solution {
    struct node {
        int index, latestSec;
        node(): index(0), latestSec(0) {}
        node(int i, int s): index(i), latestSec(s) {}
    };
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int> const& changeIndices) {
        const int n = nums.size(), m = changeIndices.size();
        // latestSecBefore[i][j] represents the index whose latest second 
        // is j when the final_sec = i.
        vector<vector<int>> latestSecBefore(m+1);
        latestSecBefore[1] = vector<int>(m+1, 0);
        latestSecBefore[1][1] = changeIndices[0];
        vector<int> helper(n+1, 0);
        helper[changeIndices[0]] = 1;
        
        for (int s = 2; s <= m; s++) {
            latestSecBefore[s] = latestSecBefore[s-1];
            const int changeIndex = changeIndices[s-1];
            latestSecBefore[s][s] = changeIndex;
            if (helper[changeIndex] > 0) {
                // cancel the old latest sec.
                latestSecBefore[s][helper[changeIndex]] = 0;
            }
            helper[changeIndex] = s;
        }

        std::function<bool(int)> f = [&](int final_sec) {
            int sum_of_marked = 0, count_of_marked = 0;
            // vector<int>(n+1);
            // this is the vector of latest seconds of n numbers.
            auto const& latestSec = latestSecBefore[final_sec];

            for (int s = 1; s <= final_sec && count_of_marked < n; s++) {
                const int changeIndex = changeIndices[s-1];
                // if s is the latest second of changeIndex.
                if (changeIndex == latestSec[s]) {
                    if (s - sum_of_marked - count_of_marked <= nums[changeIndex-1]) 
                        return false;
                    sum_of_marked += nums[changeIndex-1];
                    count_of_marked++;
                }
            }
            return count_of_marked == n;
        };

        int l = 1, r = m;
        int res = m+1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f(mid)) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        return res == m+1 ? -1 : res;
    }
};

int main() {
    vector<int> nums = {0,1}, changeIndices = {2,2,2};
    int res = Solution().earliestSecondToMarkIndices(nums, changeIndices);
    //printf("res = %d\n", res);
}
