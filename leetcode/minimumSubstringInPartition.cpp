// Date:   Wed Aug 28 20:35:35 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <algorithm>
#include <array>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>

// Leetcode 3144
class Solution {
    struct State {
        std::array<uint16_t, 26> count = { 0 };
        uint16_t min_cnt = UINT16_MAX, max_cnt = 0;
        char min_cnt_ch;
        std::string _str;

        State& operator+=(char c) {
            _str += c;
            const int idx = c - 'a';
            const uint16_t cnt = ++count[idx];
            
            if (cnt > max_cnt) {
                max_cnt = cnt;
            }

            if (cnt < min_cnt) {
                min_cnt = cnt;
                min_cnt_ch = c;
            }
            else if (c == min_cnt_ch) {
                min_cnt = cnt;
                for (int i = 0; i < 26; i++) {
                    if (count[i] && count[i] < min_cnt) {
                        min_cnt = count[i];
                        min_cnt_ch = 'a' + i;
                    }
                }
            }
            return *this;
        }

        bool balanced() const& {
            return min_cnt == max_cnt;
        }
    };

public:
    int minimumSubstringsInPartition(std::string& s) {
        // let dp[i] be the minimum number of partitions for the prefix 
        // ending at index i.
        std::vector<int> dp(s.size() + 1);
        dp[0] = 0;
        dp[1] = 1;

        for (int i = 1; i < s.size(); i++) {
            State state;
            int min_par = i+1;
            for (int j = i; j >= 0; j--) {
                state += s[j];
                if (state.balanced()) {
                    min_par = std::min(min_par, dp[j]+1);
                }
            }
            dp[i+1] = min_par;
            printf("dp[%d] = %d\n", i, min_par);
        }
        return dp[s.size()];
    }
};
<<<<<<< HEAD
=======

class BestSolution {
public:
    int minimumSubstringsInPartition(std::string& s) {
        int n = s.size();
        int maxNum = 0;
        int num = 0;
        int diffNum = 0;
        std::vector<int> dp(n + 1, INT_MAX);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {
            maxNum = 0;
            diffNum = 0;
            int m[26] = {0};
            for (int j = i; j < n; j++) {
                int c = s[j] - 'a';
                num = ++m[c];
                if (num == 1) diffNum++;
                maxNum = std::max(num, maxNum);

                if (maxNum * diffNum == j - i + 1) {
                    dp[i] = std::min(dp[i], 1 + dp[j + 1]);
                }
            }
        }

        return dp[0];
    }
};
>>>>>>> 18a930d (Leetcode 3144)
