/*
 3. 无重复字符的最长子字符串
 基本思想即建立一个滑动窗口，在滑动窗口内部所有的字符都是不一样的。
 通过一个数组m记录所有字符在已经遍历过的字符中最近出现过的位置的索引。
 当出现遍历到的字符在前面出现过时，则必须将窗口的左边界跳到最近出现过该字符的索引的下一格，以保证整个滑动窗口的字符是
 不一样的。
 数组m原本是用的map，后来发现所有的字符的数字都在128的范围内， 所以用数组直接索引更加省时。 
 */
 
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = -1, n = s.size();
        //unordered_map<int, int> m;
        int m[129];
        memset(m, 0, sizeof(m));
        for (int i = 0; i < n; ++i) {
            if (m[s[i]] != 0 && m[s[i]] > left) {
                printf("not here\n");
                left = m[s[i]];
            }
            m[s[i]] = i;
            res = max(res, i - left);            
        }
        return res;
    }
}; 
