/**********************************************
  > File Name		: longestIdealString.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug  7 16:20:52 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int longestIdealString(const string s, const int k) {
        vector<int> dp(s.size(), 0), letter_pos(26, -1);
        dp[0] = 1;
        letter_pos[s[0]-'a'] = 0;
        
        int res = 1;

        for (int i = 1; i < s.size(); i++) {
            int max_val = 0;
            const char c = s[i];
            printf("iterate %c\n", c);

            for (int j = max(0, c-'a'-k); j <= min(25, c-'a'+k); j++) {
                //max_val = max(max_val, letter_pos[j] == -1 ? 0 : dp[letter_pos[j]]);
                printf("check %c, letter_pos[%d] = %d\n", (char)(j+'a'), j, letter_pos[j]);
                if (letter_pos[j] != -1 && dp[letter_pos[j]] > max_val) {
                    printf("use %c at pos %d value: %d\n", (char)(j+'a'), letter_pos[j], dp[letter_pos[j]]);
                    max_val = dp[letter_pos[j]];
                }
            }

            dp[i] = max_val + 1;
            letter_pos[c-'a'] = i;
            printf("%c max_val: %d\n\n", c, dp[i]);

            res = max(res, dp[i]);
        }

        return res;
    }
};

int main() {
    printf("%d\n", Solution().longestIdealString("lkpkxcigcs", 6));
}
