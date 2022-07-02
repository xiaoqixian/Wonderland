/**********************************************
  > File Name		: sumOfDistanceInTree.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 14 Dec 2021 08:09:47 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <cassert>
#include <unistd.h>
#include "printv.h"
using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {

    }

    //time limit exceeded
    vector<int> sumOfDistancesInTree2(int n, vector<vector<int>>& edges) {
        vector<vector<int>> dists;
        
        for (int i = 0; i < n; i++) {
            dists.push_back(vector<int>(n, n));
            dists[i][i] = 0;
        }

        int count = n*(n-1) - 2*edges.size();
        for (vector<int>& edge: edges) {
            dists[edge[0]][edge[1]] = 1;
            dists[edge[1]][edge[0]] = 1;
        }

        vector<bool> done(n, false);
        int i, j, k;
        bool flag;
        int step = 2, temp;
        while (count) {
            for (i = 0; i < n; i++) {
                if (done[i]) {
                    continue;
                }
                flag = true;
                for (j = 0; j < n; j++) {
                    if (dists[i][j] > step) {
                        for (k = 0; k < n; k++) {
                            temp = dists[i][k] + dists[k][j];
                            if (temp <= step) {
                                dists[i][j] = temp;
                                dists[j][i] = temp;
                                count -= 2;
                                break;
                            }
                        }
                        if (dists[i][j] >= step) {
                            flag = false;
                        }
                    }
                }
                done[i] = flag;
                //printf("node %d, count = %d\n", i, count);
                //printv2(dists);
                //printf("\n");
                //sleep(1);

                if (!count) {
                    break;
                }
            }
            step++;
        }
        
        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            vector<int>& v = dists[i];
            for (int dist: v) {
                assert(dist < n);
                res[i] += dist;
            }
        }
        return res;
    }

};

int main() {
    Solution s;
    vector<vector<int>> edges = {{0,1},{0,2},{2,3},{2,4},{2,5}};
    //vector<vector<int>> edges = {{1,0}};
    vector<int> v = s.sumOfDistancesInTree(6, edges);
    printv(v);
}
