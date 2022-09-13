/**********************************************
  > File Name		: garbageCollection.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug 28 11:46:06 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        //int dist = 0, m_dist = 0, p_dist = 0, g_dist = 0;
        vector<int> dist(4, 0);
        int res = garbage[0].size();

        for (int i = 1; i < garbage.size(); i++) {
            dist[0] += travel[i-1];
            for (char c: garbage[i]) {
                int index = 0;
                switch (c) {
                    case 'M': index = 1; break;
                    case 'G': index = 2; break;
                    case 'P': index = 3; break;
                }

                res += dist[0] - dist[index] + 1;
                dist[index] = dist[0];
            }
        }
        return res;
    }
};
