/**********************************************
  > File Name		: kruskal.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 07 Aug 2020 06:42:20 PM CST
 **********************************************/

#include <iostream>
using namespace std;

/*
 * Kruskal算法原理：
 * 我们假设一个图有m个节点，n条边。
 * 首先，我们需要把m个节点看成m个独立的生成树，并且把n条边按照从小到大的数据进行排列。
 * 在n条边中，我们依次取出其中的每一条边，如果发现边的两个节点分别位于两棵树上，那么把两棵树合并成为一颗树；
 * 如果树的两个节点位于同一棵树上，那么忽略这条边，继续运行。
 * 等到所有的边都遍历结束之后，如果所有的生成树可以合并成一条生成树，那么它就是我们需要寻找的最小生成树，反之则没有最小生成树。
 *
 * 其实这个思想和幷查集有点像
 */

#include <vector>
#include <algorithm>

class Kruskal {
private:
    vector<vector<int>> graph;

public:
    Kruskal(vector<vector<int>> graph) {
        this->graph = graph;
    }

    static bool comp(vector<int> a, vector<int> b) {
        return a[2] < b[2];
    }

    //找到节点a在幷查集中的根节点
    int findRoot(vector<int>& sets, int a) {
        while (sets[a] != a) {
            a = sets[a];
        }
        return a;
    }

    //现在需要考虑的一个是如何将所有的边排序，以及排序后如何表示
    //现在用二维vector表示排序后的边
    vector<vector<int>> kruskal() {
        vector<bool> viewed(graph.size(), false);
        vector<vector<int>> edges;
        vector<int> sets(graph.size()); //幷查集
        vector<vector<int>> res(graph.size());

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] != 0) {
                    if (!viewed[i] || !viewed[j]) {
                        vector<int> edge(3);
                        edge[0] = i;
                        edge[1] = j;
                        edge[2] = graph[i][j];
                        edges.push_back(edge);
                    }
                }
            }
            sets[i] = i;
        }
        sort(edges.begin(), edges.end(), comp);
        for (int i = 0; i < edges.size(); i++) {
            vector<int> edge = edges[i];
            int root1 = findRoot(sets, edge[0]), root2 = findRoot(sets, edge[1]);
            if (root1 != root2) {
                //合并两个根节点
                sets[root2] = root1;
                res[edge[0]].push_back(edge[1]);
                res[edge[1]].push_back(edge[0]);
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> graph = {
        {0,7,0,5,0,0,0},
        {7,0,8,9,7,0,0},
        {0,8,0,0,5,0,0},
        {5,9,0,0,15,6,0},
        {0,7,5,15,0,8,9},
        {0,0,0,6,8,0,11},
        {0,0,0,0,9,11,0}
    };
    Kruskal k(graph);
    vector<vector<int>> res = k.kruskal();
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << (char)(i+'A') << " -> " << (char)(res[i][j]+'A') << endl;
        }
    }
    return 0;
}
