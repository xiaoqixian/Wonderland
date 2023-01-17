/**********************************************
  > File Name		: treeDiameter.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Jan 17 13:30:03 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

/*
 * Double DFS
 * It is provable that start at any node, do DFS to reach the farthest node A, then at 
 * A, do DFS to reach the farthest node B, and the path from A to B is the longest path.
 */
class Solution {
public:
    int treeDiameter(const int n, const vector<vector<int>>& edges) {
        vector<vector<int>> graph;
        for (const auto& e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        std::function<pair<int, int>(int, vector<bool>&&)> dfs = 
            [&](int node, vector<bool>&& visited) {
            visited[node] = true;
            int max_step = 0, max_node = node;
            for (const int link: graph[node]) {
                if (!visited[link]) {
                    auto[s, n] = dfs(link, std::move(visited));
                    if (s > max_step) {
                        max_step = s;
                        max_node = n;
                    }
                }
            }
            visited[node] = false;
            return make_pair(max_step+1, max_node);
        };

        //execute dfs twice
        auto[s1, n1] = dfs(0, vector<bool>(n, false));
        auto[s2, n2] = dfs(n1, vector<bool>(n, false));
        return n2;
    }
};
