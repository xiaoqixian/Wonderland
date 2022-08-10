/**********************************************
  > File Name		: distributeCookies.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug 10 00:01:51 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int distributeCookies(vector<int>& cookies, const int k) {
        const int n = cookies.size();
        sort(cookies.begin(), cookies.end(), std::greater<int>());
        vector<int> kid_cookie(k, 0);
        vector<uint8_t> count(k, 0);

        auto sum_op = [](const vector<uint8_t>& v) {
            return std::accumulate(v.cbegin(), v.cend(), 0);
        };

        int res = INT_MAX;
        std::function<void(int)> trace = [&](int ck) {
            for (int i = 0; i < k; i++) {
                kid_cookie[i] += cookies[ck];
                count[i] = 1;
                if (ck < n-1 && kid_cookie[i] < res && k - sum_op(count) < n - ck) {
                    trace(ck+1);
                }
                if (ck == n-1) {
                    res = min(res, kid_cookie[i]);
                }

                kid_cookie[i] -= cookies[ck];
            }
        };

        return res;
    }
};
