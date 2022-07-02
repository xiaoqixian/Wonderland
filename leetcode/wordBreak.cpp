/**********************************************
  > File Name		: wordBreak.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 01 Nov 2020 11:32:07 PM CST
  > Location        : Shanghai
 **********************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * Leetcode 140.单词拆分II
 * 首先可以利用动态规划的思想，建立一个vector<vector<string>>dp
 * dp[i]不为空表示0到i的子字符串可以被成功拆分，且拆分的语句放在dp[i]中
 * 构建字典树，且是从后向前构建。
 * 当指针k移动到s的第k位时，就从k开始往前匹配字符串，如果在字典中匹配成功，
 * 就分别与减去最后这个单词位的dp[j]中的字符串加上一个空格相加放入dp[k]中。
 * 但是还没完，第一次匹配成功后k还要继续往前匹配，直到匹配失败或者k = 0.
 * 
 * 这样，到达结尾的时候就是dp[k]就是最终结果。
 */

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        Node* root = new Node(' ', 0);
        vector<vector<string>> dp(s.size(), vector<string>());
        /* build dictionary tree */
        for (string& word: wordDict) {
            root->insert(word);
        }
        int len = s.size();
        for (int i = 0; i < len; i++) {
            int k = i;
            while (k >= 0) {
                string sub_s = s.substr(k, i-k+1);
                int search = root->exist(sub_s);
                if (search == 0) {
                    break;
                } else if (search == 1) {
                    k--;
                    continue;
                } else {
                     if (k < 1) {
                        dp[i].emplace_back(sub_s);
                    } else {
                        for (string& words: dp[k-1]) {
                            dp[i].emplace_back(words + " " + sub_s);
                        }
                    }
                }
                k--;
            }
        }
        return dp[len-1];
    }

    /* Build a dictionary tree.
     * Implemented by linked list.
     * Return the root node of the tree.
     */
    

private:
    struct Node {
        char c;
        int state; /* state is to indicate three states of a node: 1 means it's a character of a preffix, 2 means it's not only a character of a preffix, but also the last character of a preffix, 0 means it's a root node, root does not represent any character, it connects with all preffixes. */
        Node* nexts[26]{NULL};

        Node(char c, int state = 1):c(c), state(state) {
            cout << "create a node " << c << endl;
        }

        void insert(const string& suf) {
            _insert(suf);
        }

        /* check if the word suf exits in the dictionary tree */
        int exist(const string& suf) {
            cout << "checking " << suf << endl;
            return _exist(this, suf, suf.size()-1);
        }
        private:
        void _insert(const string& suf) {
            /* only the root node is allowed to insert a new sufffix*/
            if (state != 0) {
                return ;
            }
            _traverse(this, suf, suf.size()-1);
        }

        void _traverse(Node* node, const string& suf, int k) {
            char c = suf[k];
            if (node->nexts[c - 'a'] == NULL) {
                node->nexts[c - 'a'] = new Node(c);
            }
            if (k == 0) {
                node->nexts[c - 'a']->state = 2;
                return ;
            } else {
                _traverse(node->nexts[c - 'a'], suf, k-1);
            }
        }

        /* 
         * return 3 kinds of results.
         * 0: No such suffix in the dictionary tree
         * 1: suf is a part of a word in the dictionary tree.
         * 2: suf is a word in the dictionary tree
         */
        int _exist(Node* node, const string& suf, int k) {
            char ch = suf[k];
            if (node->nexts[c - 'a'] == NULL) {
                return 0;
            } else {
                if (k == 0) {
                    return node->nexts[c-'a']->state == 2 ? 2 : 1;
                } else {
                    return _exist(node->nexts[c-'a'], suf, k - 1);
                }
            }
        }
    };
};

/*
 * 我的版本虽然可以AC，但是还是超时了。
 * Leetcode的官方解答非常简洁，省去了很多重复的匹配。
 * 以及，构建一个字典树其实是很没有必要的
 * 哎，伤心
 */

class Solution {
private:
    unordered_map<int, vector<string>> ans;
    unordered_set<string> wordSet;

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        wordSet = unordered_set(wordDict.begin(), wordDict.end());
        backtrack(s, 0);
        return ans[0];
    }

    void backtrack(const string& s, int index) {
        if (!ans.count(index)) {
            if (index == s.size()) {
                ans[index] = {""};
                return;
            }
            ans[index] = {};
            for (int i = index + 1; i <= s.size(); ++i) {
                string word = s.substr(index, i - index);
                if (wordSet.count(word)) {
                    backtrack(s, i);
                    for (const string& succ: ans[i]) {
                        ans[index].push_back(succ.empty() ? word : word + " " + succ);
                    }
                }
            }
        }
    }
};

