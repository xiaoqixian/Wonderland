// Date:   Fri Aug 23 20:41:04 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <cassert>
#include <vector>
using std::vector;

class Solution {
public:
    struct node {
        long long cnt; // count of 2^* in this number so far.
        int cnt2; // count of 2 elements in this number
        node(long long c, int c2): cnt(c), cnt2(c2) {}
    };

    // static vector<node> source;

    vector<int> findProductsOfElements(vector<vector<long long>> const& queries) {
        vector<int> res(queries.size());
        // the first element is just a padding.
        vector<node> source = {node(0, 0), node(1, 0)};

        auto add_till = [&](const long long target) {
            for (long long cnt = source.back().cnt; cnt < target; cnt = source.back().cnt) {
                int num = source.size();
                int idx = 0, cnt2 = 0;
                
                while (num) {
                    if (num & 1) {
                        cnt2 += idx;
                        cnt++;
                    }
                    idx++;
                    num >>= 1;
                }
                source.emplace_back(node(cnt, cnt2));
            }
        };

        // find upperbound
        auto find_ub = [&](const long long target) {
            int l = 1, r = source.size()-1;
            while (l < r) {
                int m = l + (r - l) / 2;
                auto const& nd = source[m];
                if (target == nd.cnt) return m;
                else if (target < nd.cnt) r = m;
                else l = m + 1;
            }
            return r;
        };

        // set the low off bits of num to 0
        auto trim = [](int num, int off) {
            printf("trim: num = %d, off = %d\n", num, off);
            assert(off < 32);
            int idx = 0, cnt = 0;
            while (off--) {
                while (((num >> idx) & 1) == 0) idx++;
                assert(idx < 32);
                cnt += idx++;
            }
            return cnt;
        };

        auto print_source = [&]() {
            printf("source: {");
            for (auto const& nd: source) {
                printf("(%lld, %d), ", nd.cnt, nd.cnt2);
            }
            printf("}\n");
        };

        int qi = 0;
        for (auto const& q: queries) {
            printf("\n");
            long long from = q[0], to = q[1], mod = q[2];
            int lub, rub;
            if (to >= source.back().cnt) {
                add_till(to + 1);
                print_source();
                rub = source.size() - 1;
            } else {
                rub = find_ub(to + 1);
            }
            lub = find_ub(from + 1);
            printf("find lub = %d, rub = %d\n", lub, rub);
            assert(lub <= rub);
            int range_cnt2;

            if (lub == rub) {
                int before = source[lub-1].cnt;
                range_cnt2 = trim(lub, to - before + 1) - trim(lub, from - before);
            } else {
                range_cnt2 = source[lub].cnt2 - trim(lub, from - source[lub-1].cnt);
                // printf("range_cnt2 = %d\n", range_cnt2);
                range_cnt2 %= 64; // 64 is the size of long long
                for (int i = lub+1; i < rub; i++) {
                    range_cnt2 += source[i].cnt2;
                    range_cnt2 %= 64;
                }

                range_cnt2 += trim(rub, to - source[rub-1].cnt + 1);
                // printf("trim %lld from %d\n", to-source[rub-1].cnt+1, rub);
                // printf("range_cnt2 = %d\n", range_cnt2);
                range_cnt2 %= 64;
            }
            
            res[qi++] = (1ll << range_cnt2) % mod;
        }
        return res;
    }
};

#include "printv.hpp"
int main() {
    auto res = Solution().findProductsOfElements({{2,20,15},{12,20,18}});
    printv(res);
}
