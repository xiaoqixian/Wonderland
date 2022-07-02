/**********************************************
  > File Name		: eventualSafeNodes.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 30 Jul 2020 11:43:17 AM CST
 **********************************************/

#include <iostream>
using namespace std;

/*
 Leetcode 802.找到最终的安全状态
    虽然题目描述有点难懂，但是看来应该就是只要找出所有的环，环内的节点肯定不是结果就是了。
 然后所有存在通向环的边的节点也不是结果。

 步骤为：
 找到图中没有入边的点，即为终点。
 删除终点之后，再找到所有只有一条连向终点的出边的节点。
 */

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> res;
        //找到所有没有出度的节点
        //printf("not overflow\n");
        stack<int> s;
        unordered_map<int, vector<int>> ins;
        vector<int> outdegree(graph.size());
        for (int i = 0; i < graph.size(); i++) {
            outdegree[i] = graph[i].size();
            if (graph[i].size() == 0) {
                s.push(i);
            }
            vector<int> v = graph[i];
            for (int j = 0; j < v.size(); j++) {
                ins[v[j]].push_back(i);
            }
        }
        //printf("2not overflow\n");
        unordered_map<int, vector<int>>::iterator iter;
        while (!s.empty()) {
            int node = s.top();
            s.pop();
            res.push_back(node);
            iter = ins.find(node);
            if (iter == ins.end()) {
                //孤立的节点
                continue;
            }
            vector<int> outnodes = iter->second;
            //对于所有的没有出度节点，找连向它们的节点。如果存在出度为1的节点，就压入栈
            for (int i = 0; i < outnodes.size(); i++) {
                if (outdegree[outnodes[i]] == 1) {
                    s.push(outnodes[i]);
                }
                //由于本节点需要被删除，所以等于这些出度要减一。
                outdegree[outnodes[i]]--;
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};

/*
 * 然而，拓扑排序虽然简单易懂。
 * 但是这题最快的方式还是深度优先搜索
 */

/*
 我们同样可以使用深度优先搜索的方法判断图中的每个节点是否能走到环中。对于每个节点，我们有三种染色的方法：白色表示该节点  还没有被访问过；灰色表示该节点在栈中（这一轮搜索中被访问过）或者在环中；黑色表示该节点的所有相连的节点都被访问过，且该  节点不在环中。

 当我们第一次访问一个节点时，我们把它从白色变成灰色，并继续搜索与它相连的节点。如果在搜索过程中我们遇到一个灰色的节点，  那么说明找到了一个环，此时退出搜索，所有的灰色节点保持不变（即从任意一个灰色节点开始，都能走到环中），如果搜索过程中，  我们没有遇到灰色的节点，那么在回溯到当前节点时，我们把它从灰色变成黑色，即表示它是一个安全的节点。

 虽然运行时间还是只超过了67%
 */

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> color(graph.size(), 0);
        vector<int> res;
        for (int i = 0; i < graph.size(); i++) {
            if (dfs(i, color, graph)) {
                res.push_back(i);
            }
        }
        return res;
    }

    //定义：白色：0， 灰色：1，黑色：2
    bool dfs(int i,vector<int>& color, vector<vector<int>>& graph) {
        if (color[i] > 0) { //说明是黑色，被确认最终安全的点
            return color[i] == 2;
        }
        color[i] = 1;
        vector<int> outs = graph[i];
        for (int j = 0; j < outs.size(); j++) {
            if (color[outs[j]] == 2) continue;
            if (color[outs[j]] == 1 || !dfs(outs[j], color, graph)) {
                return false;
            }
        }
        color[i] = 2;
        return true;
    }
};
