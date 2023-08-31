/**********************************************
  > File Name		: minimumTotalPrice.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Apr 16 12:00:48 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    /*
    对于任意一次旅行选择的路径而言，若经过2k个结点，则有k个结点可减半、k个不可。
    若经过2k+1个结点，则有k+1个结点减半，k个不可；或k个结点减半，k+1个不可。
    n个结点的树只有n-1条边，说明是最小生成树，说明每趟旅行只有唯一的一条路径。
    将每条路径分为两部分和，一部分和是从开始结点每隔一个结点计算，另一部分和是从第二个结点每隔一个结点计算。
    */
    struct trip {
        int odd_price, even_price;
        int node_num;
    };

    int minimumTotalPrice(const int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<vector<bool>> graph(n, vector<bool>(n, false));
        vector<vector<trip>> trip_price(n, vector<trip>(n));
        int res = INT_MAX;

        for (int i = 0; i < n; i++) graph[i][i] = true;
        for (const auto& e: edges) {
            graph[e[0]][e[1]] = true;
            graph[e[1]][e[0]] = true;
        }
        
        std::function<void(const int)> dfs = [&](const int source) {
            trip_price[source][source] = {price[source], 0, 1};
            for (int node = source + 1; node < n; node++) {
                if (graph[source][node]) {
                    dfs(node);
                    for (int end = node; end < n; end++) {
                        if (graph[node][end]) {
                            const trip& t = trip_price[node][end];
                            trip_price[source][end] = {price[source] + t.even_price, t.odd_price, t.node_num+1};
                        }
                    }
                }
            }
        };

        dfs(0);

        auto calc_price_backwards = [](const trip& t) {
            if (t.node_num % 2)
                return t.odd_price/2 + t.even_price;
            else return t.even_price/2 + t.odd_price;
        };

        for (int node = 0; node < n; node++) {
            int path_sum = 0;
            for (auto& t: trips) {
                if (t[0] > t[1]) swap(t[0], t[1]);
                const int source = t[0], end = t[1];
                if (source <= node && end >= node) {
                    const auto& path1 = trip_price[source][node], path2 = trip_price[node][end];
                    //if (path1.node_num % 2)
                        //path_sum += path1.odd_price/2 + path1.even_price;
                    //else path_sum += path1.even_price/2 + path1.odd_price;
                    path_sum += calc_price_backwards(path1);
                    path_sum += path2.odd_price/2 + path2.even_price;
                    path_sum -= price[node]/2;
                } else if (source <= node && end <= node) {
                    path_sum += calc_price_backwards(trip_price[source][node]);
                    path_sum -= calc_price_backwards(trip_price[end][node]);
                    path_sum += trip_price[end][node].node_num % 2 ? price[end]/2 : price[end];
                } else {
                    const auto& path1 = trip_price[node][source], path2 = trip_price[node][end];
                    path_sum += path2.odd_price/2 + path2.even_price;
                    path_sum -= path1.odd_price/2 + path1.even_price;
                    path_sum += path1.node_num % 2 ? price[source]/2 : price[source];
                }
            }
            res = min(res, path_sum);
        }
        return res;
    }
};
