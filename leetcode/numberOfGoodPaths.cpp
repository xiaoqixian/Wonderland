/**********************************************
  > File Name		: numberOfGoodPaths.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep 25 11:29:04 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stack>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int numberOfGoodPaths(const vector<int>& vals, const vector<vector<int>>& edges) {
        const int n = vals.size();
        int res = n;
        vector<vector<int>> graph(n);
        vector<int> id(n), disjoint_set(n), size(n, 1);

        for (const auto& eg: edges) {
            graph[eg[0]].push_back(eg[1]);
            graph[eg[1]].push_back(eg[0]);
        }

        std::iota(id.begin(), id.end(), 0);
        std::iota(disjoint_set.begin(), disjoint_set.end(), 0);

        std::sort(id.begin(), id.end(), [&](int i, int j) {return vals[i] < vals[j];});

        std::function<int(int)> find = [&](int x) {
            return disjoint_set[x] == x ? x : disjoint_set[x] = find(disjoint_set[x]);
        };

        for (const int x: id) {
            const int vx = vals[x], fx = find(x);
            for (const int y: graph[x]) {
                const int fy = find(y);
                if (fy == fx || vals[fy] > vx) continue;

                if (vx == vals[fy]) {
                    res += size[fx] * size[fy];
                    size[fx] += size[fy];
                }
                disjoint_set[fy] = fx;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int numberOfGoodPaths(const vector<int>& vals, const vector<vector<int>>& _edges) {
        int n = vals.size(), res = 0;
        stack<int> tree_path, path;

        vector<vector<int>> edges(n);
        vector<bool> visited(n, false);
        set<pair<int, int>> us;

        for (const auto& eg: _edges) {
            edges[eg[0]].push_back(eg[1]);
            edges[eg[1]].push_back(eg[0]);
        }

        std::function<void(stack<int>&, int, vector<bool>&)> dfs = [&](stack<int>& path, const int start, vector<bool>& visited) {
            assert(!visited[start]);
            visited[start] = true;

            stack<int> keeper;
            while (!path.empty() && vals[start] > vals[path.top()]) {
                keeper.push(path.top());
                path.pop();
            }

            stack<int> equal_keeper;
            while (!path.empty() && vals[start] == vals[path.top()]) {
                if (us.find({start, path.top()}) == us.end()) res++;
                us.insert({start, path.top()});
                equal_keeper.push(path.top());
                path.pop();
            }

            while (!equal_keeper.empty()) {
                path.push(equal_keeper.top());
                equal_keeper.pop();
            }
            path.push(start);

            for (int node: edges[start]) {
                if (!visited[node]) {
                    dfs(path, node, visited);
                }
            }

            visited[start] = false;
            assert(!path.empty() && path.top() == start);
            path.pop();

            while (!keeper.empty()) {
                path.push(keeper.top());
                keeper.pop();
            }
        };

        for (int i = 0; i < n; i++) {
            if (edges[i].size() == 1)
                dfs(path, i, visited);
        }
        return (res >> 1) + n;
    }
};

int main() {
    vector<int> vals = {1,3,2,1,3};
    vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4}};
    printf("%d\n", Solution().numberOfGoodPaths(vals, edges));
    printf("%d\n", Solution2().numberOfGoodPaths(vals, edges));
}
