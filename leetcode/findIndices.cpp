// Date: Sun Oct 15 11:26:31 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector> 
#include <queue>

class Solution {
public:
    std::vector<int> findIndices(
            std::vector<int> const& nums, 
            const int indexDifference, 
            const int valueDifference) {
        const int n = nums.size();

        auto const min_pq_cmp = [&](const int i, const int k) {
            if (nums[i] == nums[k])
                return k > i;
            else return nums[i] > nums[k];
        };
        auto const max_pq_cmp = [&](const int i, const int k) {
            if (nums[i] == nums[k])
                return k > i;
            else return nums[i] < nums[k];
        };

        std::priority_queue<int, std::vector<int>, decltype(min_pq_cmp)> min_pq(min_pq_cmp);
        std::priority_queue<int,std::vector<int>, decltype(max_pq_cmp)> max_pq(max_pq_cmp);

        //init pq
        for (int i = indexDifference; i < n; i++) {
            min_pq.push(i);
            max_pq.push(i);

            if (abs(nums[i] - nums[0]) >= valueDifference) 
                return {0, i};
        }
        
        for (int i = 1; i < n - indexDifference; i++) {
            //we lost nums[i-1+indexDifference];
            const int lost = i - 1 + indexDifference;

            if (nums[i] > nums[i-1]) {
                while (min_pq.top() <= lost)
                    min_pq.pop();

                if (abs(nums[i] - nums[min_pq.top()]) >= valueDifference)
                    return {i, min_pq.top()};
            }
            else if (nums[i] < nums[i-1]) {
                while (max_pq.top() <= lost)
                    max_pq.pop();

                if (abs(nums[i] - nums[max_pq.top()]) >= valueDifference)
                    return {i, max_pq.top()};
            }
        }
        return {-1, -1};
    }
};
