/**********************************************
  > File Name		: findRedundantConnection.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 28 Jul 2020 10:37:00 AM CST
 **********************************************/

#include <iostream>
using namespace std;

/*
 Leetcode 684.冗余连接

 判断图中是否有环，肯定是要用拓扑排序。

 找到图的起点，然后不断删除入度与出度不一致的边。直到所有的边的入度与出度一致。
 如果还存在边，则说明存在环。按道理来说，删除环的任意一边都可以将其改造为树。
 所以只要返回环中位于数组最后面的边就好了。
 */

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        //map<int, vector<int>> conn;
        map<int, int> degree;
        for (int i = 0; i < edges.size(); i++) {
            //conn[edges[i][0]].push_back(edges[i][1]);
            //conn[edges[i][1]].push_back(edges[i][0]);
            degree[edges[i][0]]++;
            degree[edges[i][1]]++;
        }
        //找到起点和终点，两者的入度和出度不一致。在无向图中就是相连的边的数量为奇数。
        int a = -1, b = -1;
        //map<int, int>::iterator iter;
        bool flag = true;
        while (flag) {
            flag = false;
            for (int i = 0; i < edges.size(); i++) {
                a = degree[edges[i][0]];
                b = degree[edges[i][1]];
                if (a == 0 || b == 0) {
                    continue;
                }
                if (a == 1 || b == 1) {
                    degree[edges[i][0]]--;
                    degree[edges[i][1]]--;
                    flag = true;
                }
            }
        }
        for (int i = edges.size()-1; i >= 0; i--) {
            if (degree[edges[i][0]] != 0 && degree[edges[i][1]] != 0) {
                return edges[i];
            }
        }
        vector<int> res;
        return res;
    }
};

/*
 * 看来只有我想到了要用拓扑排序做，其他人都是用的幷查集
 * 由于存在多个循环，所以时间上很吃亏，只击败了5%的用户
 */

/*
 * 从幷查集的思路来看，所谓那条冗余的边就是已经属于同一个集合的两个点
 * 再连起来的一条边。
 *
 * 我做树做多了，老是想着要另外写一个结构体代表树的节点，但是这里节点
 * 的值其实不重要。所以直接写一个vector，索引的值就代表节点的值，索引
 * 对应的值就是节点的指向。
 */

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> rp(1001);
        int sz = edges.size();
        // 初始化各元素为单独的集合，代表节点就是其本身
        for(int i=0;i<sz;i++)
            rp[i] = i;
        for(int j=0;j<sz;j++){
            // 找到边上两个节点所在集合的代表节点
            int set1 = find(edges[j][0], rp);
            int set2 = find(edges[j][1], rp);
            if(set1 == set2)  // 两个集合代表节点相同，说明出现环，返回答案
                return edges[j]; 
            else    // 两个集合独立，合并集合。将前一个集合代表节点戳到后一个集合代表节点上
                rp[set1] = set2;
        }
        return {0, 0};
    }

    // 查找路径并返回代表节点，实际上就是给定当前节点，返回该节点所在集合的代表节点
    // 之前这里写的压缩路径，引起歧义，因为结果没更新到vector里，所以这里改成路径查找比较合适
    // 感谢各位老哥的提议
    int find(int n, vector<int> &rp){
        int num = n;
        while(rp[num] != num)
            num = rp[num];
        return num;
    }
};


