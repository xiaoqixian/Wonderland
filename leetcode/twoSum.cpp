/*
 Leetcode: 1.����֮��
 ���������ҵ�����ʹ�����ǵĺ͵�����target����
 ����ʹ��ɢ�б��������ڱ���ʱ����ʹ��targeet��ȥ�����������������ɢ�б����м�¼��˵����Ӧ����֮ǰ���ֹ��� 
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
