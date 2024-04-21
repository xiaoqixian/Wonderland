// Date:   Sun Apr 21 11:44:46 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using std::vector;

class Solution {
    struct edge {
        int index, end, weight;
        edge(int i, int e, int w):
            index(i), end(e), weight(w) {}
    };
public:
    vector<bool> findAnswer(const int n, vector<vector<int>>& edges) {
        // first find all shortest paths.
        vector<vector<edge>> graph(n);
        for (int i = 0; i < edges.size(); ++i) {
            auto const& e = edges[i];
            graph[e[0]].emplace_back(edge(i, e[1], e[2]));
            graph[e[1]].emplace_back(edge(i, e[0], e[2]));
        }

        std::priority_queue<
            std::pair<long long, int>,
            vector<std::pair<long long, int>>,
            std::greater<>> pq;

        vector<long long> dists(n, std::numeric_limits<long long>::max());
        vector<bool> visited(n);
        
        pq.emplace(std::make_pair(0ll, 0));

        while (!pq.empty()) {
            auto const [d, i] = pq.top();
            pq.pop();
            if (visited[i]) continue;

            visited[i] = true;
            dists[i] = d;

            for (auto const& e: graph[i]) {
                if (visited[e.end]) continue;
                pq.emplace(std::make_pair(d + e.weight, e.end));
            }
        }

        vector<bool> res(edges.size());

        if (dists[n-1] < std::numeric_limits<long long>::max()) {
            visited = vector<bool>(n, false);
            std::queue<int> q;
            q.push(n-1);

            while (!q.empty()) {
                const int node = q.front();
                q.pop();
                if (visited[node]) continue;
                visited[node] = true;

                for (auto const& e: graph[node]) {
                    if (dists[e.end] + e.weight != dists[node]) 
                        continue;
                    res[e.index] = true;
                    q.push(e.end);
                }
            }
        }

        return res;
    }
};
