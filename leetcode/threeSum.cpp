/*
 Leetcode: 15.����֮��
 ����vector�е���������ÿ�α���������Ϊ����֮�͵���Сֵ��Ȼ�������������Ƚ�����������ֻ��Ҫ��˫ָ����������Ժ������
 
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
