/**********************************************
  > File Name		: buisiestServer.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 05 Jan 2022 09:40:27 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include "printv.h"
using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<pair<int, int>> server_loads = vector<pair<int, int>>(k, make_pair(0, 0));
        vector<int> server_finishes = vector<int>(k, 0);
        int n = arrival.size();

        for (int i = 0; i < n; i++) {
            int index = i % k, t = index, time = arrival[i];
            int tsp = server_loads[index].first, server_load = server_loads[index].second;
            while (tsp + server_load > time) {
                ++t %= k;
                if (t == index)
                    break;
                tsp = server_loads[t].first, server_load = server_loads[t].second;
            }

            if (t == index) //can't find an avaliable server
                continue;

            server_loads[t] = make_pair(time, load[i]);
            server_finishes[t]++;
        }

        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_finishes[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_finishes[i];
            } else if (server_finishes[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    vector<int> arrival = {1,2,3,4,5}, load = {5,2,3,3,3};
    Solution s;
    vector<int> res = s.busiestServers(3, arrival, load);
    printv(res);
}
