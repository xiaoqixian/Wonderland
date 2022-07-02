/*
 Leetcode: 310.最小高度树 

 第一种方法：暴力破解
 那么问题就转化成了从图中一节点找到最大高度。这里可以借助Dijkstra算法，在Dijkstra算法中只要将所有路径的权设为1
 那么就可以找到最短路径和最长路径。

 第二种方法：拓扑排序
 本题其实就是拓扑排序的变式。就是不断缩小图，直至剩下1、2个点，return。
    然而，此题的变式点如下：

    本题为无向图，所以删除的点是入度为1的点。
    本题不能一个一个的删除入度为1的点，而应在一个循环中，一次性删除入度为1的点，使得以同样的速度缩小图，直至剩      下<=2个点为止。之所以这么说是因为如果存在超过2个点，则一定会在3个点产生一个深度更小的点，所以最终结果总是
    等于2的。

 实际代码中分为两个循环，第一个循环是直到最终结果小于等于2，第二个循环是在edges中找到入度为1的边并删除。
 */

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        if (n == 2) {
            return {0,1};
        }
        /*首先要初始化一下图graph和入度indegree。
          graph是一个二维的vector，其有n行，graph[i]的vector存储着与i点相连的所有点
          indegree则是一个一维数组，在索引处表示相应点的入度
         */
        vector<int> v; //用作初始化graph，无实际用处
        vector<vector<int>> graph(n, v);
        vector<int> indegree(n, 0);
        for (int i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
            indegree[edges[i][0]]++;
            indegree[edges[i][1]]++;
        }

        int count = 0; //count表示indegree中入度为1的数量
        queue<int> q; //q用来存储当前入度为1的点
        //第一次计算indegree中入度为1的数量
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1) {
                count++;
                q.push(i);
            }
        }

        while (n > 2) {
            n -= count;
            while (count--) {
                int tmp = q.front();
                q.pop();
                indegree[tmp] = 0;
                /*
                 对于每一个入度为1的点，在删除时需要做两件事：
                 1. 在其所相连端点中删除自己
                 2. 将入度减1
                 */
                for (int i = 0; i < graph[tmp].size(); i++) { //这里因为graph中不会实际删除点，所以需要根据大小判断
                    if (indegree[graph[tmp][i]] != 0) {
                        indegree[graph[tmp][i]]--;
                        if (indegree[graph[tmp][i]] == 1) {
                            q.push(graph[tmp][i]);
                        }
                    }
                }
            }
            count = q.size();
        }
        vector<int> result;
        while (!q.empty())
        {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};
