/*
 懂了，通过建立一个有向图，有向图的边从分子指向分母，边的权值就设为计算的结果。当然有向并不代表是单向的，边是双向的，
 但是两个方向的权值不一样。
 那么，要计算某两个数的商，就是要找到从分子到分母的路径，并将沿路的权值相乘。按理说，对于任何路径，最终结果都是一样的。
 所以连寻找最短路径都不需要了。

 则对于我来说，重点在于如何构建这个图。如果不看内存使用的话，可以使用一个map对应每个变量的出度，而出度由于具有权值，所以
 也需要一个map来表示，所以是两个map的嵌套。而且权值要用double来表示，想想就知道内存肯定很大。
 */


class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        map<string, map<string, double>> graph;
        for (int i = 0; i < equations.size(); i++) {
            if (graph.find(equations[i][0]) == graph.end()) {//说明在graph不存在这个变量
                map<string, double> mole_edge;//分子边
                graph.insert(pair<string, map<string, double>>(equations[i][0], &new_edge));
                new_edge.insert(pair<string, double>(equations[i][1], values[i]));
            }
            else {
                graph[equations[i][0]].insert(pair<string, double>(equations[i][1], values[i]));
            }
            if (graph.find(equations[i][1]) == graph.end()) {
                map<string, double> deno_edge;//分母边
                graph.insert(pair<string, map<string, double>>(equations[i][1], &deno_edge));
                deno_edge.insert(pair<string, double>(equations[i][0], 1/values[i]));
            }
            else {
                graph[equations[i][1]].insert(pair<string, double>(equations[i][0], 1/values[i]));
            }
        }
        
        /*对于queries里面的算式，首先在graph里面根本找不到的变量肯定是计算不出来的，因为找不到任何关联
          其次，也可能存在两个根本不相干的图，所以必须能够找到一条路径。
         */
        
    }
};
