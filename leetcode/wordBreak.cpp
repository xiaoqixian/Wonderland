/**********************************************
  > File Name		: wordBreak.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 01 Nov 2020 11:32:07 PM CST
  > Location        : Shanghai
 **********************************************/
#include <iostream>
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
        
    }

    /* Build a dictionary tree.
     * Implemented by linked list.
     * Return the root node of the tree.
     */
    

private:
    struct Node {
        char c;
        int state; /* state is to indicate three states of a node: 0 means no such next, 1 means it's a character of a preffix, 2 means it's not only a character of a preffix, but also the last character of a preffix, 3 means it's a root node, root does not represent any character, it connects with all kinds of preffixes. */
        Node* nexts[26];
        static void insert(const string& pre) {
            _insert(pre, 0);
        }
        private:
        void _insert(const string& pre, int k) {
            /* only the root node is allowed to insert a new preffix*/
            if (state != 3) {
                return ;
            }
            

        }
    };

};
