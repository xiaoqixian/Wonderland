/**********************************************
  > File Name		: longestCircle.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Aug  2 13:59:31 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestCycle(vector<int>& edges) {
        const int n = edges.size();
        vector<int> indeg(n, 0);

        for (int n: edges) {
            if (n == -1)
                continue;
            indeg[n]++;
        }
    
        vector<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0)
                q.push_back(i);
        }

        while (!q.empty()) {
            int v = edges[q.back()];
            q.pop_back();
            indeg[v]--;

            if (indeg[v] == 0)
                q.push_back(v);
        }

        unordered_set<int> visited;
        auto travel = [&](const int start) {
            int dist = 0;
            visited.insert(start);
            int node = edges[start];
            
            while (node != start) {
                dist++;
                visited.insert(node);
                node = edges[node];
            }
            return dist;
        };

        int res = -1;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0 || visited.contains(i))
                continue;
            res = max(res, travel(i));
        }
        return res;
    }
};

class Solution1 {
public:
    int longestCycle(vector<int>& edges) {
        const int n = edges.size();
        vector<bool> visited(n, false);

        int res = -1;
        auto travel = [&](const int start) {
            int dist = 1, node = edges[start];
            visited[start] = true;
            if (node == -1)
                return -1;

            vector<bool> visited_dup = visited;

            while (node != start) {
                if (visited[node] || edges[node] == -1) {
                    dist = -1;
                    break;
                } else if (visited_dup[node]) {
                    int tail = start;
                    while (tail != node) {
                        dist--;
                        tail = edges[tail];
                    }
                    break;
                }

                visited_dup[node] = true;
                node = edges[node];
                dist++;
            }
            visited = visited_dup;
            return dist;
        };

        for (int node = 0; node < n; node++) {
            if (!visited[node]) {
                res = max(res, travel(node));
            }
        }
        return res;
    }
};
 
int main() {
    vector<int> v = {2,-1,3,1};
    Solution().longestCycle(v);
}
