/**********************************************
  > File Name		: countBits.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 09 Oct 2020 03:00:11 PM CST
 **********************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        if (num == 0) {
            return {0};
        }
        if (num == 1) {
            return {0,1};
        }
        vector<int> res(num+1);
        int index = 1;
        int temp = 2;
        res[0] = 0;
        res[1] = 1;
        while (temp <= num) {
            int loop = 1 << index;
            for (int i = 0;temp <= num && i < loop; i++) {
                //res.push_back(res[temp - loop + i]);
                res[temp] = res[temp - loop + i] + 1;
                temp++;
            }
            index++;
        }
        return res;
    }
};
