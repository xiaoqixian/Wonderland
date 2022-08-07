/**********************************************
  > File Name		: sellingWood.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Aug  6 21:14:26 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <queue>
#include <set>
using namespace std;

/*
 * 这道题与常规动态规划不同的点在于无法得到递推公式。
 * 要卖出木块，需要长宽两个维度的值都满足，不像一般的
 * 动态规划一样只需要满足一个值。
 *
 * dp[i][j] 
 */
//int _dp_prev[201][201], _dp[201][201];
typedef long long ll;
class Solution {
public:
    long long sellingWood(const int m, const int n, const vector<vector<int>>& prices) {
        vector<vector<ll>> dp(m+1, vector<ll>(n+1, 0));

        {
            const int height = prices[0][0], width = prices[0][1], price = prices[0][2];
            for (int h = height; h <= m; h++) {
                for (int w = width; w <= n; w++) {
                    dp[h][w] = (h/height)*(w/width)*price;
                }
            }
        }

        const int size = prices.size();
        for (int i = 0; i < size; i++) {
            printf("round %d\n", i);
            const int height = prices[i][0], width = prices[i][1], price = prices[i][2];

            if (dp[height][width] >= price) continue;

            for (int h = height; h <= m; h++) {
                for (int w = width; w <= n; w++) {
                    ll max_val = 0;
                    bool flag = true;
                    int max_h_num = h/height, max_w_num = w/width;
                    for (int h_num = 1; flag && h_num <= max_h_num; h_num++) {
                        const int th = h_num * height;
                        for (int w_num = 1; flag && w_num <= max_w_num; w_num++) {
                            const int tw = w_num * width;
                            ll temp = max(dp[h][w], price*h_num*w_num + max(dp[h-th][w] + dp[th][w-tw], dp[h][w-tw] + dp[h-th][tw]));

                            if (temp > max_val)
                                max_val = temp;
                            else flag = false;
                        }
                    }
                    dp[h][w] = max_val;
                }
            }
        }
        return dp[m][n];
    }
};

class BestSolution {
private:
    struct Result {
        long long price=0;
        int opt_h=1, opt_w=1;
    };

public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        vector<Result> dp(m * n);
        auto at = [&](int h, int w) -> Result& {return dp[(h - 1) * n + w - 1];};
        for(auto &&p: prices){
            at(p[0], p[1]) = Result{p[2], p[0], p[1]};
        }
        auto update_status = [&](int h, int w, long long v, int opt_h, int opt_w){
            auto &r = at(h, w);
            if(v > r.price){
                r = Result{v, opt_h, opt_w};
            } else if(v == r.price){
                r = Result{v, min(opt_h, r.opt_h), min(opt_w, r.opt_w)};
            }
        };
        vector<vector<int>> optimized_hs(n);
        vector<int> optimized_ws;
        for(int h = 1; h <= m; h++){
            optimized_ws.clear();
            for(int w = 1; w <= n; w++){
                auto &&curr = at(h, w);
                if(curr.opt_h == h){
                    optimized_hs[w - 1].push_back(h);
                }
                if(curr.opt_w == w){
                    optimized_ws.push_back(w);
                }
                for(int h2: optimized_hs[w - 1]){
                    if(h2 > curr.opt_h || h2 + h > m){
                        break;
                    }
                    update_status(h2 + h, w, curr.price + at(h2, w).price, h2, w);
                }
                for(int w2: optimized_ws){
                    if(w2 > curr.opt_w || w2 + w > n){
                        break;
                    }
                    update_status(h, w2 + w, curr.price + at(h, w2).price, h, w2);
                }
            }
        }
        return at(m, n).price;
    }
};
