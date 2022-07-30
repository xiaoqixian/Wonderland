/**********************************************
  > File Name		: shortestSequence.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 30 17:06:50 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
    int shortestSequence(vector<int>& rolls, int k) {
        int res = 1, i = 0;
        const int n = rolls.size();
        vector<bool> appear(k+1, false);
        int count = k;

        while (i < n) {
            const int r = rolls[i];
            if (!appear[r]) {
                appear[r] = true;
                count--;

                if (count == 0) {
                    res++;
                    appear = vector<bool>(k+1, false);
                    count = k;
                }
            }
            i++;
        }
        return res;
    }
};
