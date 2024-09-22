// Date:   Sun Sep 22 11:11:00 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <array>
#include <cstdio>
#include <string>
using std::string;

class Solution {
public:
    long long validSubstringCount(string word1, string const& word2) {
        const int n1 = word1.length();
        if (word1.length() < word2.length()) return 0;
        std::array<int, 26> cnt = { 0 };
        for (int i = 0; i < word2.length(); i++) {
            cnt[word2[i] - 'a']++;
        }

        int state = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] > 0) {
                state |= 1 << i;
            }
        }

        long long res = 0;
        {
            const int idx = word1[0] - 'a';
            const int want = --cnt[idx];
            if (want == 0) {
                state &= ~(1 << idx);
            }
        }

        int l = 0;
        for (int r = 1; r < n1;) {
            for (; r < n1 && state > 0; r++) {
                const int idx = word1[r] - 'a';
                const int want = --cnt[idx];
                if (want == 0) {
                    state &= ~(1 << idx);
                }
            }
            if (state == 0) {
                // printf("left = %d, right = %d\n", l, r);
                res += n1 - r + 1;
                // printf("res += %d\n", n1 - r + 1);
                const int idx = word1[l++] - 'a';
                const int want = ++cnt[idx];
                if (want > 0) {
                    state |= 1 << idx;
                }
            }
        }

        while (l < n1 && state == 0) {
            if (state == 0) {
                res++;
            }

            const int idx = word1[l++] - 'a';
            if (++cnt[idx] > 0) {
                state |= 1 << idx;
            }
        }
        return res;
    }
};

int main() {
    string a = "ddccdddccdddccccdddccdcdcd", b = "ddc";
    printf("%zd\n", a.length());
    printf("%lld\n", Solution().validSubstringCount(a, b));
}
