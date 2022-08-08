/**********************************************
  > File Name		: longestSubsequence.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Aug  8 14:03:35 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <bitset>
#include <iostream>
using namespace std;

class Solution {
public:
    int longestSubsequence(const string s, const int k) {
        const int n = s.size();
        int counter = 0, unset = 0;

        auto unset_highest_bit = [](int& val) {
            int i = 1;
            while (i < 32) {
                if (val < (1<<i)) break;
                i++;
            }
            i--;
            val &= ~(1<<i);
            return true;
        };

        int res = 1, val = s[0] - '0';
        for (int i = 1; i < n; i++) {
            const int digit = s[i] - '0';
            if ((val << 1) + digit <= k) {
                res++;
            } else if (val > 0) {
                unset_highest_bit(val);
            }
            val = (val << 1) + digit;
        }

        return res;
    }

};

int main() {
    //string s = "001010101011010100010101101010010";
    string s = "111100010000011101001110001111000000001011101111111110111000011111011000010101110100110110001111001001011001010011010000011111101001101000000101101001110110000111101011000101";
    //const int k = 93951055;
    const int k = 11713332;
    printf("%d\n", Solution().longestSubsequence(s, k));
    //printf("%d\n", Solution().longestSubsequence("0010101010110", 93));
    //printf("%d\n", Solution().longestSubsequence("1001010", 5));
}
