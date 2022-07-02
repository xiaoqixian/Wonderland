/*
 Leetcode: 1.两数之和
 在数组中找到两个使得它们的和等于数target的数
 考虑使用散列表来做，在遍历时，先使用targeet减去遍历到的数，如果在散列表中有记录，说明对应的数之前出现过。 
 */ 
 
#include <vector>
#include <stdio.h>
#include <string>
#include <map>
using namespace std;
 
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        map<int, int> record;
        int i;
        for (i = 0; i < nums.size(); i++) {
        	int complete = target - nums[i];
        	if (record.find(complete) != record.end()) {
        		res.push_back(i);
        		res.push_back(record[complete]);
			}
			record[nums[i]] = i;
		}
    }
};

int main() {
	string s = "abc";
	printf("%d\n", s[1]);
	return 0;
}
