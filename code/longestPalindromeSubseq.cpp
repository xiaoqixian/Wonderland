/**********************************************
  > File Name		: longestPalindromeSubseq.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 04 Feb 2022 08:18:08 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <string>
#include <vector>
#include <stdio.h>
#include "printv.h"
using namespace std;

int longestPalindromeSubseq(string s) {
    int n = s.size();
    // dp 数组全部初始化为 0
    vector<vector<int>> dp(n, vector<int>(n, 0));
    // base case
    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    // 反着遍历保证正确的状态转移
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            // 状态转移方程
            if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    printv2(dp);
    // 整个 s 的最长回文子串长度
    return dp[0][n - 1];
}

int longestPalindromeSubseq2(string s) {
    int n = s.size();
    // base case：一维 dp 数组全部初始化为 0
    vector<int> dp(n, 1);

    for (int i = n - 2; i >= 0; i--) {
        int pre = 0;
        for (int j = i + 1; j < n; j++) {
            int temp = dp[j];
            // 状态转移方程
            if (s[i] == s[j])
                dp[j] = pre + 2;
            else
                dp[j] = max(dp[j], dp[j - 1]);
            pre = temp;
        }
    }
    return dp[n - 1];
}

int main() {
    string s = "AHEEHA";
    printf("%d\n", longestPalindromeSubseq(s));
}
