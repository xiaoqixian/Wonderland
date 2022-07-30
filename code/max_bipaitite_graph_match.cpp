/**********************************************
  > File Name		: max_bipaitite_graph_match.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 09 Aug 2020 11:39:42 AM CST
 **********************************************/

#include <iostream>
using namespace std;

/*
 * 匈牙利算法实现的最大二分图匹配
 */

#include <vector>

class Hungarian {
private:
    vector<vector<int>> graph;
    vector<int> matched;

public:
    Hungarian(vector<vector<int>> graph) {
        this->graph = graph;
    }

    vector<int> maxBipartiteGraphMatch() {
        //matched实际要与被匹配的节点数量一致
        //我这里由于两边集合的节点数相等，所以直接用匹配节点数代替
        matched = vector<int>(graph.size(), -1);
        for (int i = 0; i < graph.size(); i++) {
            match(i);
        }
        return matched;
    }

    //递归函数
    bool match(int node) {
        for (int i = 0; i < graph[node].size(); i++) {
            cout << "node: " << node << "  graph[node][i]:" << graph[node][i] << endl;
            if (matched[graph[node][i]] == -2) continue;
            else if (matched[graph[node][i]] == -1) {
                matched[graph[node][i]] = node;
                return true;
            } else {
                int tmp = matched[graph[node][i]];
                matched[graph[node][i]] = -2; //-2表示进入暂时匹配状态
                if (match(tmp)) {
                    matched[graph[node][i]] = node;
                    return true;
                } else {
                    matched[graph[node][i]] = tmp;
                    continue;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> graph = {
        {0,1},
        {1,2},
        {0,1},
        {2}
    };
    Hungarian h(graph);
    vector<int> res = h.maxBipartiteGraphMatch();
    for (int i = 0; i < res.size(); i++) {
        cout << (char)(res[i] + 'A') << " -> " << (char)(i+'W') << endl;
    }
    return 0;
}
