/********************************************
 > File Name       : maxIncreasingCells.cpp
 > Author          : lunar
 > Email           : lunar_ubuntu@qq.com
 > Created Time    : Sun May 28 14:56:22 2023
 > Copyright@ https://github.com/xiaoqixian
********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    struct cell {
        int val, row, col;
    };

    struct rank {
        int val, step;
    };

    int maxIncreasingCells(vector<vector<int>>& mat) {
        const int m = mat.size(), n = mat.at(0).size();
        vector<vector<int>> cache(m, vector<int>(n, 0));

        vector<vector<rank>> row_best(m, {{INT_MIN, 0}}), col_best(n, {{INT_MIN, 0}});
        vector<cell> unfold(m * n);
        for (int i = 0; i < m; i++) {
            const int base = i*n;
            for (int j = 0; j < n; j++) {
                unfold[base + j] = {mat[i][j], i, j};
            }
        }

        sort(unfold.begin(), unfold.end(), [](const cell& c1, const cell& c2) {
            return c1.val < c2.val;
        });
        
        for (const cell& c: unfold) {
            int rb = 0, cb = 0;
            auto& cell_row = row_best.at(c.row);
            auto& cell_col = col_best.at(c.col);
            for (auto ri = cell_row.rbegin(); ri != cell_row.rend(); ri++) {
                if (c.val > ri->val) {
                    rb = ri->step;
                    break;
                }
            }
            for (auto ri = cell_col.rbegin(); ri != cell_col.rend(); ri++) {
                if (c.val > ri->val) {
                    cb = ri->step;
                    break;
                }
            }
            const int cur_step = max(rb, cb) + 1;
            if (cur_step > cell_row.back().step) {
                if (c.val> cell_row.back().val)
                    cell_row.push_back({c.val, cur_step});
                else cell_row.back().step = cur_step;
            }
            if (cur_step > cell_col.back().step) {
                if (c.val > cell_col.back().val)
                    cell_col.push_back({c.val, cur_step});
                else cell_col.back().step = cur_step;
            }
        }
        int res = 0;
        for (const auto& v: row_best) res = max(res, v.back().step);
        for (const auto& v: col_best) res = max(res, v.back().step);
        return res;
    }
};
