/**********************************************
  > File Name		: leetcode/findItineraray.cpp
  > Author			: lunar
  > Mail			: lunar_ubuntu@qq.com
  > Created Time	: Sat 18 Jul 2020 12:40:20 PM CST
 ****************************************/

#include <iostream>
using namespace std;

/*
 Leetcode 332.重新安排行程
 本题主要考察图中欧拉路径的寻找。
 */

class Solution {
public:
    unordered_map<string, multiset<string>> g; //multiset允许元素重复
    vector<string> ans;
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto &ticket : tickets) g[ticket[0]].insert(ticket[1]);
        dfs("JFK");
        return vector<string>(ans.rbegin(), ans.rend());
    }

    //这段深度优先搜索的关键在于欧拉路径的寻找
    //反正欧拉路径就是要找到一条边，删除后以另一端点进行递归，我还没有搞清楚原理
    void dfs(string ver)
    {
        while (g[ver].size())
        {
            string next = *g[ver].begin();
            g[ver].erase(g[ver].begin());
            dfs(next);
        }
        ans.push_back(ver);
    }
};


