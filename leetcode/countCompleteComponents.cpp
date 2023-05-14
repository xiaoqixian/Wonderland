#include <vector>
using namespace std;

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> root(n), nodes_num(n, 1), edges_num(n, 0);
        for (int i = 0; i < n; i++) root[i] = i;
        std::function<int(int)> find_root = [&](int node) {
            return root[node] == node ? node : (root[node] = find_root(root[node]));
        };

        auto merge = [&](int x, int y) {
            const int rx = find_root(x), ry = find_root(y);
            if (rx != ry) {
                if (nodes_num[rx] >= nodes_num[ry]) {
                    nodes_num[rx] += nodes_num[ry];
                    edges_num[rx] += edges_num[ry] + 1;
                    root[ry] = rx;
                } else {
                    nodes_num[ry] += nodes_num[rx];
                    edges_num[ry] += edges_num[rx] + 1;
                    root[rx] = ry;
                }
            } else {
                edges_num[rx]++;
            }
        };


        for (auto const& e: edges) {
            merge(e[0], e[1]);
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (root[i] == i) {
                const int expect = nodes_num[i] * nodes_num[i-1] / 2;
                assert(expect >= edges_num[i]);
                res += expect == edges_num[i];
            }
        }
        return res;
    }
};
