/**********************************************
  > File Name		: minimumCost.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun May  7 00:17:17 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    struct node {
        int x, y, cost;
    };

    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        unordered_map<pair<int, int>, int> node_id;
        int count = 0;
        node_id.insert({{start[0], start[1]}, count++});
        node_id.insert({{target[0], target[1]}, count++});
        for (auto const& sr: specialRoads) {
            auto f = node_id.find({sr[0], sr[1]});
            if (f == node_id.end())
                node_id.insert({{sr[0], sr[1]}, count++});
            f = node_id.find({sr[2], sr[3]});
            if (f == node_id.end())
                node_id.insert({{sr[2], sr[3]}, count++});
        }

        vector<pair<int, int>> id_cord(count);
        for (auto const& [k, v]: node_id) {
            id_cord[v] = k;
        }

        vector<vector<int>> graph(count, vector<int>(count));

    }
};
