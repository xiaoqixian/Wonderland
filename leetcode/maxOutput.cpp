/**********************************************
  > File Name		: maxOutput.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Jan 16 21:29:20 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution1 {
public:
    long long maxOutput(const int n, const vector<vector<int>>& edges, const vector<int>& price) {
        long long res = 0;
        vector<vector<int>> graph(n);

        std::function<long long(int, vector<bool>&&)> visit = [&](int node, vector<bool>&& visited) {
            long long max_sum = 0;
            visited[node] = true;
            for (const int link: graph[node]) {
                if (!visited[link]) {
                    max_sum = max(max_sum, visit(link, std::move(visited)));
                }
            }
            visited[node] = false;
            return max_sum + price[node];
        };

        for (const auto& e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        for (int i = 0; i < n; i++) {
            res = max(res, visit(i, vector<bool>(n, false)) - price[i]);
        }
        return res;
    }
};

class Solution {
public:
    long long maxOutput(int n, vector<vector<int>> &edges, vector<int> &price) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x); // 建树
        }

        long ans = 0;
        // 返回带叶子的最大路径和，不带叶子的最大路径和
        function<pair<long, long>(int, int)> dfs = [&](int x, int fa) -> pair<long, long> {
            long p = price[x], max_s1 = p, max_s2 = 0;
            for (int y : g[x])
                if (y != fa) {
                    auto[s1, s2] = dfs(y, x);
                    // 前面最大带叶子的路径和 + 当前不带叶子的路径和
                    // 前面最大不带叶子的路径和 + 当前带叶子的路径和
                    ans = max(ans, max(max_s1 + s2, max_s2 + s1));
                    max_s1 = max(max_s1, s1 + p);
                    max_s2 = max(max_s2, s2 + p); // 这里加上 p 是因为 x 必然不是叶子
                }
            return {max_s1, max_s2};
        };
        dfs(0, -1);
        return ans;
    }
};
