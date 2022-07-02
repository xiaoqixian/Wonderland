/*面试题17.13 恢复空格*/

/*
 听说要同时运用字典树和动态规划才能解题

 字典树用于迅速判断sentence的某个子字符串是否存在于字典中

 而动态规划，其实这个问题和背包问题非常像。但有一个很大的不同是在背包问题中决定要不要拿一个物品时，如果拿掉，
 剩下的空间可以看作一个整体。但是本问题，如果选择某个子字符串可以识别，则剩下的两端的子字符串不能串在一起看。
 这时就需要同时考虑两边的动态规划效果。

 在位置i处，从后往前开始判断从j(j < i)到i的子字符串是否属于字典，如果不属于则dp[i] = dp[i-1]+1
 如果属于，则转移方程为dp[i] = min(dp[i], dp[j-1])
 
 */


class Trie {
public:
    Trie* next[26] = {nullptr};
    bool isEnd;
    
    Trie() {
        isEnd = false;
    }

    void insert(string s) {
        Trie* curPos = this;

        for (int i = s.length() - 1; i >= 0; --i) {
            int t = s[i] - 'a';
            if (curPos->next[t] == nullptr) {
                curPos->next[t] = new Trie();
            }
            curPos = curPos->next[t];
        }
        curPos->isEnd = true;
    }
};

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        int n = sentence.length(), inf = 0x3f3f3f3f;

        Trie* root = new Trie();
        for (auto& word: dictionary) {
            root->insert(word);
        }

        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;

            Trie* curPos = root;
            for (int j = i; j >= 1; --j) {
                int t = sentence[j - 1] - 'a';
                if (curPos->next[t] == nullptr) {
                    break;
                } else if (curPos->next[t]->isEnd) {
                    dp[i] = min(dp[i], dp[j - 1]);
                }
                if (dp[i] == 0) {
                    break;
                }
                curPos = curPos->next[t];
            }
        }
        return dp[n];
    }
};

