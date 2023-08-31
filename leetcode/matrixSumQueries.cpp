/********************************************
 > File Name       : matrixSumQueries.cpp
 > Author          : lunar
 > Email           : lunar_ubuntu@qq.com
 > Created Time    : Tue Jun  6 23:12:40 2023
 > Copyright@ https://github.com/xiaoqixian
********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    long long matrixSumQueries(const int n, vector<vector<int>> const& queries) {
        vector<vector<bool>> seen(2, vector<bool>(n, false));
        int row_count = n, col_count = n;
        long long res = 0;
        
        for (auto it = queries.rbegin(); it != queries.rend(); it++) {
            const int type = it->at(0), index = it->at(1), val = it->at(2);
            if (seen[type][index]) continue;
            seen[type][index] = true;

            if (type) {
                res += (long long)val * row_count;
                col_count--;
            } else {
                res += (long long)val * col_count;
                row_count--;
            }
        }
        return res;
    }
};
