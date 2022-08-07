/**********************************************
  > File Name		: reachableNodes.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug  7 10:50:35 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& rest) {
        vector<bool> restricted(n, false), visited(n, false);
        int res = 1;
        
        for (int node: rest) {
            restricted[node] = true;
        }
        
        //sort(edges.begin(), edges.end(), [](const auto& e1, const auto& e2) {return e1[0] < e2[0];});
        unordered_map<int, vector<int>> tree;
        for (const vector<int>& e: edges) {
            auto it = tree.find(e[0]);
            if (it == tree.end()) {
                it->second.push_back(e[1]);
            } else {
                tree.insert({e[0], vector<int>({e[1]})});
            }
        }
        
        auto it = tree.find(0);
        queue<vector<int>> q({it->second});
        visited[0] = true;
        while (!q.empty()) {
            const vector<int>& reach_nodes = q.front();
            for (int node: reach_nodes) {
                if (visited[node] || restricted[node])
                    continue;

                res++;
                visited[node] = true;
                auto it = tree.find(node);
                if (it != tree.end())
                    q.push(it->second);
            }
            q.pop();
        }
        return res;
    }
};
