/**********************************************
  > File Name		: distinctNames.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug 10 14:23:09 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    long long distinctNames(vector<string> &ideas) {
        unordered_map<string, int> group;
        for (auto &s : ideas)
            group[s.substr(1)] |= 1 << (s[0] - 'a');
        long ans = 0L;
        int cnt[26][26] = {};
        for (auto &[_, mask] : group)
            for (int i = 0; i < 26; i++)
                if ((mask >> i & 1) == 0) { //没有以i开头的, 则以j开头的同后缀名可以与任何以i开头的词搭配。
                    for (int j = 0; j < 26; j++)
                        if (mask >> j & 1) ++cnt[i][j];
                } else {//有以i开头的，则将该单词作为第一个单词
                    for (int j = 0; j < 26; j++)
                        if ((mask >> j & 1) == 0) ans += cnt[i][j];
                }
        return ans * 2;
    }
};


