/**********************************************
  > File Name		: minReverseOperations.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Apr 12 21:07:23 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    /*
     * consider this problem as a state machine problem.
     * index p denotes a unique state.
     * every state can transfer to other states by flipping.
     */
    vector<int> minReverseOperations2(
            const int n, 
            const int p, 
            const vector<int>& banned, 
            const int k) {
        vector<int> res(n, -1);
        vector<bool> visited(n, false);
        queue<pair<int, int>> q;
        int count = n - banned.size() - 1;
        res[p] = 0; visited[p] = true;
        q.push({p, 0});

        for (const int b: banned) visited[b] = true;

        while (count && !q.empty()) {
            const auto [pp, step] = q.front();
            q.pop();

            const int min_limit = max(0, k-pp-1);
            const int max_limit = min(k-1, n-pp-1);

            for (int t = min_limit; t <= max_limit; t++) {
                const int new_p = pp - k + 1 + t*2;
                if (!visited[new_p]) {
                    visited[new_p] = true;
                    q.push({new_p, step+1});
                    res[new_p] = step+1;
                    count--;
                }
            }
        }
        return res;
        typedef std::enable_if<true, void>::type type;
    }
};
