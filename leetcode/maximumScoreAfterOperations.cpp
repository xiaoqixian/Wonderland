// Date: Sun Nov 05 11:02:11 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <cassert>
#include <vector> 
#include <numeric>
#include <queue>

class Solution {
public:
    long long maximumScoreAfterOperations(
            std::vector<std::vector<int>>& edges, 
            std::vector<int>& values) {
        long long res = 0;
        const int n = values.size();

        std::vector<std::vector<int>> bridges(n, std::vector<int>());
        std::vector<std::vector<int>> tree(n, std::vector<int>());
        std::vector<int> parent(n, -1);
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        std::queue<int> q2;

        for (auto const& e: edges) {
            bridges[e[0]].push_back(e[1]);
            bridges[e[1]].push_back(e[0]);
        }

        q2.push(0);
        while (!q2.empty()) {
            const int node = q2.front();
            q2.pop();
            visited[node] = true;

            for (const int ch: bridges[node]) {
                if (visited[ch]) continue;
                tree[node].push_back(ch);
                parent[ch] = node;
                q2.push(ch);
            }

            if (tree[node].empty())
                q.push(node);
        }


        // for a tree, we can either keep the root healthy
        // and take all the values in the subtree, or we can 
        // take the root value and try to keep all subtree healthy
        //
        // let health_cost[i] be the minimum value to keep the tree
        // rooted at i healthy.
        std::vector<long long> health_cost(n, 0);

        while (!q.empty()) {
            const int i = q.front();
            q.pop();
            long long ch_cost = 0;
            for (const int ch: tree[i]) {
                if (!health_cost[ch]) {
                    ch_cost = INT_MAX;
                    break;
                }

                ch_cost += health_cost[ch];
            }

            if (!ch_cost)
                health_cost[i] = values[i];
            else if (!values[i])
                health_cost[i] = ch_cost;
            else 
                health_cost[i] = std::fmin(values[i], ch_cost);

            if (parent[i] >= 0)
                q.push(parent[i]);
        }

        long long total_value =
            std::accumulate(
                    values.cbegin(), 
                    values.cend(), 
                    (long long)0);

        return total_value - health_cost[0];
    }
};
