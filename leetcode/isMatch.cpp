/**********************************************
  > File Name		: isMatch.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 26 Jul 2021 04:42:19 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class Solution {
public:
    bool isMatch(string s, string p) {
        size_t sz = s.size();
        size_t pz = p.size();
        vector<vector<bool>> matched(sz, vector<bool>(pz, false));

        int i = 0, j = 0;
        char c, pc, prev;
        while (i < sz && j < pz) {
            c = s[i]; pc = p[j];
            if (c == pc || pc == '.') {
                matched[i][j] = i == 0 ? true : matched[i-1][j-1];
                prev = pc;
                i++; j++;
            }
            else if (pc == '*' && (prev == pc || prev == '.')) {
                matched[i][j] = true;
                i++;
            }
            else {
                if ()
            }
        }
    }
}
