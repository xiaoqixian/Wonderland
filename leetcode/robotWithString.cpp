/**********************************************
  > File Name		: robotWithString.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Oct  9 11:05:12 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <queue>
#include <stack>
using namespace std;

class Solution {
public:
    string robotWithString(string s) {
        auto comp = [](const pair<char, int>& p1, const pair<char, int>& p2) {
            if (p1.first == p2.first) {
                return p1.second > p2.second;
            } else return p1.first > p2.first;
        };

        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(comp)> pq(comp);
        stack<char> t;
        int index = 0;
        const int n = s.size();
        string res = "";

        for (int i = 0; i < n; i++) {
            pq.push({s[i], i});
        }

        while (index < n) {
            while (!pq.empty() && pq.top().second < index) 
                pq.pop();
            if (pq.empty()) break;

            const auto& top = pq.top();
            
            while (!t.empty() && t.top() <= top.first) {
                res += t.top();
                t.pop();
            }

            while (index < top.second) {
                t.push(s[index++]);
            }

            res += s[index];
            index = top.second+1;
            pq.pop();
        }

        while (index < n) {
            t.push(s[index++]);
        }

        while (!t.empty()) {
            res += t.top();
            t.pop();
        }
        return res;
    }
};

#include <iostream>
int main() {
    cout << Solution().robotWithString("vzhofnpo") << endl;
}
