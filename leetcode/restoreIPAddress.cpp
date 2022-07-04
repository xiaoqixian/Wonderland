/**********************************************
  > File Name		: restoreIPAddress.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 11:03:58 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
#include <iostream>
#include <format>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        return recurse(s, 4);
    }

    vector<string> recurse(string s, int k) {
        if (s.size() == 0 || s.size() > k << 2)
            return {};

        if (k == 1) {
            cout << "k = " << k << ", s = " << s << endl;
            if (s.size() > 1 && s[0] == '0')
                return {};
            if (s.size() > 2 && stoi(s) > 255)
                return {};
            return {s};
        }

        vector<string> res;
        int len = s.size() < 3 ? s.size() : 3;
        for (int i = 1; i <= len; i++) {
            string cur = s.substr(0, i);
            cout << "k = " << k << ", cur = " << cur << endl;
            if (i > 1 && cur[0] == '0')
                continue;
            if (i == 3 && stoi(cur) > 255)
                continue;

            cout << "put " << s.substr(i, s.size()-i) << " after" << endl;
            vector<string> after = recurse(s.substr(i, s.size()-i), k-1);
            for (const auto& a: after) {
                res.push_back(cur + "." + a);
            }
        }
        return res;
    }
};

void printvs(const vector<string>& vs) {
    for (const auto& s: vs) {
        cout << "\"" << s << "\", ";
    }
    cout << endl;
}

int main() {
    auto res = Solution().restoreIpAddresses("0279245587303");
    printvs(res);
}
