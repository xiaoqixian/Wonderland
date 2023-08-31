/********************************************
 > File Name       : longestValidSubstring.cpp
 > Author          : lunar
 > Email           : lunar_ubuntu@qq.com
 > Created Time    : Sun Jul 16 13:39:03 2023
 > Copyright@ https://github.com/xiaoqixian
********************************************/

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        const int n = word.size();
        unordered_set<string> us(forbidden.cbegin(), forbidden.cend());
        int res = 0;
        for (int right = 0, left = 0; right < n; right++) {
            for (int i = right; i >= left && i > right-10; i--) {
                if (us.count(word.substr(i, right-i+1))) {
                    left = i+1;
                    break;
                }
            }
            res = max(res, right-left+1);
        }
        return res;
    }
};
