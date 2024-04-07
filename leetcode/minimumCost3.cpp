// Date:   Sun Apr 07 21:46:11 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

// 392 Weekly Contest.
// 100244. Minimum Cost Walk in Weighted Graph

#include <cassert>
#include <functional>
#include <vector>
#include <unordered_map>
using std::vector;

class Solution {
    struct node {
        int dist;
        int size;
    };
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> disjoint_set(n);
        std::unordered_map<int, node> group;

        for (int i = 0; i < n; ++i) 
            disjoint_set[i] = i;
        
        std::function<int(int)> find = [&](int node) {
            if (disjoint_set[node] == node) 
                return node;
            else 
                return disjoint_set[node] = find(disjoint_set[node]);
        };

        for (auto const& e: edges) {
            const int u = e[0], v = e[1], w = e[2];
            const int ur = find(u), vr = find(v);
            auto f1 = group.find(ur), f2 = group.find(vr);

            // printf("\nu = %d, v = %d, w = %d, ur = %d, vr = %d\n", u,v,w,ur,vr);
            
            if (f1 != group.end() && f2 != group.end()) {
                if (ur == vr) {
                    f1->second.dist &= w;
                } else {
                    auto big = f1, small = f2;
                    int br = ur, sr = vr;
                    if (f1->second.size < f2->second.size) {
                        std::swap(big, small);
                        std::swap(br, sr);
                    }

                    // printf("1. join root %d, original dist = %d, ", br, big->second.dist);

                    disjoint_set[sr] = br;
                    big->second.dist &= (small->second.dist & w);
                    big->second.size += small->second.size;

                    group.erase(small);
                    // printf("dist = %d\n", big->second.dist);
                }
            } 
            else if (f1 != group.end()) {
                disjoint_set[vr] = ur;
                f1->second.size++;
                // printf("2. join root %d, original dist = %d, ", ur, f1->second.dist);
                f1->second.dist &= w;
                // printf("dist = %d\n", f1->second.dist);
            }
            else if (f2 != group.end()) {
                disjoint_set[ur] = vr;
                f2->second.size++;
                f2->second.dist &= w;
                // printf("3. join root %d , dist = %d\n", vr, f2->second.dist);
            } 
            else {
                disjoint_set[vr] = ur;
                group.insert({ur, node { w, 2 }});
                // printf("4. join root %d , dist = %d\n", ur, w);
            }
        }

        vector<int> res(query.size(), -1);
        for (int i = 0; i < query.size(); ++i) {
            auto const& q = query[i];
            const int u = q[0], v = q[1];
            
            if (u == v) {
                res[i] = 0;
                continue;
            }

            // printf("query for %d to %d\n", u, v);
            const int ur = find(u), vr = find(v);
            if (ur != vr) {
                continue;
            }

            auto f = group.find(ur);
            assert(f != group.end());
            res[i] = f->second.dist;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> edges = {{0,4,7},{3,5,1},{1,3,5},{1,5,1}},
        query = {{0,4},{1,5},{3,0},{3,3},{3,2},{2,0},{7,7},{7,0}};
    auto res = s.minimumCost(9, edges, query);
    for (auto const i: res) {
        // printf("res = %d\n", i);
    }
}
