/**********************************************
  > File Name		: closestMeetingNode.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Aug  2 11:04:33 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
private:
    struct NodeDist {
        int node, dist;
        NodeDist(int node, int dist): node(node), dist(dist) {}
        
        bool operator<(const NodeDist& other) const {
            if (this->node == other.node)
                return this->dist < other.dist;
            return this->node < other.node;
        }
    };
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        const int n = edges.size();
        vector<NodeDist> nd1, nd2;

        auto visit = [&](int node, vector<NodeDist>& nd) {
            int dist = 0;
            vector<bool> visited(n, false);
            visited[node] = true;
            nd.push_back(NodeDist(node, 0));

            while (edges[node] != -1) {
                node = edges[node];
                if (visited[node])
                    break;

                dist++;
                visited[node] = true;
                nd.push_back(NodeDist(node, dist));
            }
        };

        visit(node1, nd1);
        visit(node2, nd1);

        sort(nd1.begin(), nd1.end());
        //sort(nd2.begin(), nd2.end());

        for (int i = 0; i < nd1.size()-1; i++) {
            const NodeDist& n1 = nd1[i], n2 = nd1[i+1];
            
            if (n1.node == n2.node) {
                nd2.push_back(NodeDist(n1.node, max(n1.dist, n2.dist)));
            }
        }

        sort(nd2.begin(), nd2.end(), [](const NodeDist& n1, const NodeDist& n2) {
            if (n1.dist == n2.dist) {
                return n1.node < n2.node;
            }
            return n1.dist < n2.dist;
        });
        return nd2.empty() ? -1 : nd2.front().node;
    }
};

int main() {}
