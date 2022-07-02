/*
 Leetcode: 15.三数之和
 遍历vector中的所有数，每次遍历的数作为三数之和的最小值。然后由于数组事先进行排序，所以只需要用双指针遍历数组以后的区域。
 
 */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int i;
        int mid, max;
        unordered_map<int, int*> m;
        for (i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int comp = 0 - nums[i];
            mid = i + 1, max = nums.size() - 1;
            while (mid < max) {
                if (nums[mid] + nums[max] == comp) {
                    printf("i = %d\n", i);
                    res.push_back({nums[i], nums[mid], nums[max]});
                    while (mid < max && nums[mid] == nums[mid+1]) mid++;
                    while (mid < max && nums[max] == nums[max-1]) max--;
                    mid++; max--;
                }
                else {
                    if (nums[mid] + nums[max] < comp) mid++;
                    else max--;
                }
            }
        }
        return res;
    }
};
