/**********************************************
  > File Name		: matchReplacement.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug 10 20:18:06 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        const int range = 'z' - '0';
        bool new_mappings[128][128] = {};

        for (int i = '0'; i <= 'z'; i++) {
            new_mappings[i][i] = true;
        }

        for (const auto& m: mappings) {
            new_mappings[m[0]][m[1]] = true;
        }

        const int n = s.size(), sn = sub.size();
        vector<char> path(sn);

        std::function<bool(char, int)> trace = [&](const char target, const int index) {
            if (!new_mappings[sub[index]][target])
                return false;
            if (index == sn-1) return true;
            return trace(target, index+1);
        };

        for (int i = 0; i <= n-sn; i++) {
            if (trace(s[i], 0))
                return true;
        }
        return false;
    }
};
