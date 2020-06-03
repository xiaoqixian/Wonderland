/*
 LeetCode: 1042.不邻接植花 
 这题本质上是个染色问题
 首先建立图的邻接表，如果建立邻接矩阵的话会栈溢出。
 遍历所有的节点，在4种花中去除相邻节点已经种了的?，然后选择一种种上。
 */

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        //建立邻接表
        vector<int> adj[N];
        for (int i = 0; i < paths.size(); i++) {
            adj[paths[i][0]-1].push_back(paths[i][1] - 1);
            adj[paths[i][1]-1].push_back(paths[i][0] - 1);
        }
        //遍历所有花园，种上其相邻花园都没有种的?
        vector<int> res(N, 0);
        int size;
        for (int i = 0; i < N; i++) {
            int breeds[] = {1,2,3,4};   
            size = adj[i].size();
            for (int j = 0; j < size; j++) {
                if (res[adj[i][j]] != 0) {
                    breeds[res[adj[i][j]] - 1] = 0;
                }
            }
            //这里根据四色定理，是一定还有没有被相邻花园种植的品种的?的
            for (int k = 0; k < 4; k++) {
                if (breeds[k] != 0) {
                    res[i] = breeds[k];
                    break;
                }
            }
        }
        return res;
    }
};
