/**********************************************
  > File Name		: canReach.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 06 Mar 2022 11:06:54 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <stack>
#include <iostream>
#include <stdio.h>
using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        stack<int> path;
        path.push(0);

        return this->trace(s, minJump, maxJump, path);
    }

    bool trace(string& s, int minJump, int maxJump, stack<int>& path) {
        int curr = path.top();
        int forward = curr + maxJump >= s.size() ? s.size()-1 : curr + maxJump;
        int limit = curr + minJump;
        if (limit >= s.size())
            return false;
        while (forward >= limit) {
            if (s[forward] == '0') {
                path.push(forward);
                if (forward == s.size() - 1 || this->trace(s, minJump, maxJump, path))
                    return true;
                path.pop();
            }
            forward--;
        }
        return false;
    }
};

int main() {
    string s = "01101110";
    cout << Solution().canReach(s, 2, 3) << endl;
}
