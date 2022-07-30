/**********************************************
  > File Name		: canChange.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 23 21:42:30 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
using namespace std;

class Solution {
public:
    bool canChange(string start, string target) {
        const int len = start.size();
        if (len != target.size())
            return false;

        if (len <= 1) return true;

        //check L first
        int i = 0, k = 0;
        while (i < len && k < len) {
            while (k < len && target[k] != 'L') k++;

            if (k == len) {
                while (i < len && start[i] != 'L') i++;

                if (i != len) return false; //more L in start than target.
                
                break;
            }
                
            while (i < len) {
                bool out = false;
                switch (start[i]) {
                    case 'R':
                        if (i >= k)
                            return false;
                        break;

                    case 'L':
                        out = true;
                        break;

                    default:
                        break;
                }
                if (i > k && target[i] == 'R') return false;
                if (out) break;
                i++;
            }

            if (i < k) return false;
            i++; k++;
        }

        if (i >= len && k < len) {
            while (k < len && target[k] != 'L') k++;
            if (k != len) return false;
        } else if (i < len && k >= len) {
            while (i < len && start[i] != 'L') i++;
            if (i != len) return false;
        }

        i = len-1, k = len-1;
        while (i >= 0 && k >= 0) {
            while (k >= 0 && target[k] != 'R') k--;

            if (k < 0) {
                while (i >= 0 && start[i] != 'R') i--;
                if (i >= 0) return false; //more R in start than target.
                break;
            }

            while (i >= 0) {
                bool out = false;
                switch (start[i]) {
                    case 'L':
                        if (i <= k)
                            return false;
                        break;

                    case 'R':
                        out = true;
                        break;

                    default:
                        break;
                }
                i--;
                if (out) break;
            }
            if (i > k) return false;
            i--; k--;
        }
        if (i < 0 && k >= 0) {
            while (k >= 0 && target[k] != 'R') k--;
            if (k >= 0) return false;
        } else if (i >= 0 && k < 0) {
            while (i >= 0 && start[i] != 'R') i--;
            if (i >= 0) return false;
        }

        return true;
    }
};
