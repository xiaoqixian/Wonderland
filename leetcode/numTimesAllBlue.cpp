/**********************************************
  > File Name		: maxTimesAllBlue.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 24 Dec 2021 03:20:03 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include "printv.h"
using namespace std;

#define MAX 0xffffffff //max value of u64
class Solution {
public:
    int numTimesAllBlue1(vector<int>& flips) {
        vector<uint64_t> nums;
        int index = -1; //index means elements from 0 to index(include index) in nums are all equal to MAX.
        int base, offset;
        int count = 0, res = 0, count_base, count_offset;
        uint64_t temp, expect;

        for (int f: flips) {
            f--;
            count++;
            base = f / 64;
            
            while (base >= nums.size()) {
                nums.push_back(0);
            }

            offset = f % 64;
            temp = 1<<offset;

            if (nums[base] & temp) {
                nums[base] ^= temp;
            } else {
                nums[base] |= temp;
            }

            count_base = count / 64;
            count_offset = count % 64;

            expect = ((uint64_t)1<<count_offset)-1;
            printf("expect = %x, flip = %d,  ", expect, f+1);

            if ((count_base == nums.size() && expect == 0) || nums[count_base] == expect) {
                //check nums before count_base
                bool flag = true;
                for (int i = 0; flag && i < count_base; i++) {
                    if (nums[i] < MAX) {
                        flag = false;
                        break;
                    }
                }
                for (int i = count_base+1; flag && i < nums.size(); i++) {
                    if (nums[i] > 0) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    res++;
                }
            }
            printvxu(nums);
        }
        return res;
    }

    int numTimesAllBlue2(vector<int>& flips) {
        int res = 0, cur_max = 0;
        for (int i = 0; i < flips.size(); i++) {
            cur_max = flips[i] > cur_max ? flips[i] : cur_max;
            if (cur_max == i+1) {
                res++;
            }
        }
        return res;
    }
};

void print_steps(vector<int>& flips) {
#define len 128
    char string[len];
    for (int i = 0; i < len; i++) {
        string[i] = '0';
    }
    int count = 0;
    for (int f: flips) {
        string[f] = string[f] == '0' ? '1' : '0';
        count++;
        if (count < 10)
            printf("step%d : %s\n", count, string);
        else 
            printf("step%d: %s\n", count, string);
    }
}

int main() {
    //vector<int> flips = {4, 1, 2, 3};
    //vector<int> flips = {1,9,11,29,5,6,7,8,4,10,3,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,30,2,31};
    vector<int> flips = {1,2,43,4,5,15,7,8,9,10,11,12,13,36,6,35,17,18,19,20,21,22,23,63,25,26,27,28,29,30,31,64,39,34,16,14,37,38,33,40,41,42,3,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,24,64,65,66,67};
    Solution s;
    print_steps(flips);
    printf("%d\n", s.numTimesAllBlue(flips));
}
