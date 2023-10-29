// Date: Sun Oct 29 13:30:21 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

// Leetcode 100108

#include <vector>
#include <cassert>
#include <functional>

class Solution {
public:
    int maximumPoints(
        std::vector<std::vector<int>>& edges, 
        std::vector<int>& coins, 
        const int k
    ) {
        // let dp[x][t] be the maximum points we can get from
        // the subtree rooted at the node x and the second operation
        // has be used t times by the ancestors (subtree root x is 
        // not included).
        
        // note that the coin number of every node is <= 10^4.
        // which means when t >= 14, the coin number of all nodes
        // in subtree is 0.
        // 
        // so we can define vector<vector<int>> dp[n, 14].

        const int max_fold_times = 14;
        const int n = coins.size();
        std::vector<std::vector<int>> 
            dp(n, std::vector<int>(max_fold_times, -1));

        // first reform the tree.
        // let tree[x] be the collection of all children nodes
        // of node x.
        std::vector<std::vector<int>> tree(n, std::vector<int>());
        std::vector<int> parent(n, -1);

        for (auto& e: edges) {
            if (e[0] > e[1]) std::swap(e[0], e[1]);
            tree[e[0]].push_back(e[1]);
            parent[e[1]] = e[0];
        }

        int res = 0;

        // t represent the times ancestors used the second operation.
        std::function<void(int, int)> dfs = 
            [&](const int node, const int t) 
        {
            if (dp[node][t] >= 0) return;

            const int node_coin = coins[node] >> t;
            // if this is a leaf node
            if (tree[node].empty()) {
                dp[node][t] = std::max(node_coin >> 1, node_coin - k);
                return;
            }

            // if choose the first operation
            int first_op_coin = node_coin - k;
            for (const int ch: tree[node]) {
                dfs(ch, t);
                first_op_coin += dp[ch][t];
            }

            // if choose the second operation
            int second_op_coin = node_coin >> 1;
            if (t < max_fold_times-1) {
                for (const int ch: tree[node]) {
                    dfs(ch, t+1);
                    second_op_coin += dp[ch][t+1];
                }
            }

            dp[node][t] = std::max(first_op_coin, second_op_coin);
        };

        dfs(0, 0);
        return dp[0][0];
    }
};
