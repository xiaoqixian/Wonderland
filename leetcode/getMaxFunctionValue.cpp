// Date: Mon Aug 28 13:56:57 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <algorithm>
#include <numeric>
#include <vector>
#include <stack>
#include <iostream>
#include <optional>

class Solution {
    struct Node {
    public:
        int dist_to_ring, ring_index;
        Node(int d, int ri):
            dist_to_ring(d),
            ring_index(ri)
        {}
    };

    template <typename T>
    void printv(std::vector<T> const& v) {
        if (v.empty()) {
            std::cout << "[]" << std::endl;
            return;
        }

        std::cout << "[" << v.at(0);
        for (auto it = v.cbegin()+1; it != v.cend(); it++)
            std::cout << ", " << *it;
        std::cout << "]" << std::endl;
    }
public:
    long long getMaxFunctionValue(std::vector<int> const& receiver, const long long k) {
        //Consider receiver as many rings with tails, the tail length can be 0
        //Every Node should be connected to a ring, the length from an 
        //Node to its ring should be recorded.
        //If an Node is in the ring, its length is 0. 
        
        //first collect rings in the receivers
        const int n = receiver.size();
        std::vector<std::vector<int>> rings;
        std::vector<bool> visited(n, false);
        std::vector<std::optional<Node>> ring_info(n);
        std::vector<int> degrees(n, 0);
        long long res = 0;

        for (int i = 0; i < n; i++) {
            degrees[i]--;
            degrees[receiver[i]]++;
        }

        std::function<void(int)> dfs = [&](const int start_id) {
            std::stack<int> st;
            
            st.push(start_id);
            while (!st.empty()) {
                const int id = st.top();

                if (!visited[id]) {
                    visited[id] = true;
                    st.push(receiver[id]);
                    continue;
                }

                st.pop();
                auto& curr = ring_info[id];

                if (curr) {
                    //previously collected ring Node
                    continue;
                }

                auto const& next = ring_info[receiver[id]];

                if (next) {
                    curr = std::optional(Node(next.value().dist_to_ring+1, next.value().ring_index));
                } else {
                    //create a new ring
                    std::vector<int> ring;
                    int rid = id;
                    const int ring_index = rings.size();
                    //collect ring
                    do {
                        ring.push_back(rid);
                        ring_info[rid] = std::optional(Node(0, ring_index));
                        rid = receiver[rid];
                        st.pop();
                    } while (rid != id);

                    rings.push_back(ring);
                }
            }
        };

        //build rings
        for (int i = 0; i < n; i++) {
            if (degrees[i] < 0)
                dfs(i);
        }

        for (int i = 0; i < n; i++) {
            if (!degrees[i] && !visited[i])
                dfs(i);
        }

        //printf("rings: \n"); for (auto const& r: rings) printv(r);

        visited = std::vector<bool>(n, false);

        std::vector<long long> ring_sum(rings.size());
        std::transform(
                rings.cbegin(),
                rings.cend(),
                ring_sum.begin(),
                [](auto const& it) {
                        return std::accumulate(
                                it.cbegin(), 
                                it.cend(), 
                                (long long)0
                            );
                    }
                );

        std::function<void(int, long long)> start_from = [&](const int start_id, long long step) {
            long long sum = 0;
            auto const [dist, ring_index] = ring_info[start_id].value();
            int rid = start_id, limit = fmin(step, dist);

            step -= limit;

            while (limit--) {
                sum += rid;
                rid = receiver[rid];
            }

            if (step) {
                assert(ring_info[rid].value().dist_to_ring == 0);
                sum += (step / rings[ring_index].size()) * ring_sum[ring_index];

                int rmd = step % rings[ring_index].size();
                while (rmd--) {
                    sum += rid;
                    rid = receiver[rid];
                }
            }
            
            sum += rid;

            res = fmax(res, sum);
            visited[start_id] = true;
            int sid = start_id;

            while (!visited[receiver[sid]]) {
                sum -= sid;
                sid = receiver[sid];
                rid = receiver[rid];
                sum += rid;
                res = fmax(res, sum);
                visited[sid] = true;
            }
        };

        for (int id = 0; id < n; id++) {
            if (degrees[id] < 0)
                start_from(id, k);
        }
        for (int id = 0; id < n; id++) {
            if (!degrees[id] && !visited[id])
                start_from(id, k);
        }
        return res;
    }
};
