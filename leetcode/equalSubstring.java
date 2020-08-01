/**********************************************
  > File Name		: equalSubstring.java
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 01 Aug 2020 11:56:59 PM CST
 **********************************************/
/*
 Leetcode 1208.尽可能使字符串相等
 所以这一题实际上是一个子数组求和小于特定值求最大长度的问题

 设立两个指针，一个作为子字符串的起始点，另一个作为终止点。
 起始点从0开始遍历，但是终止点并不是遍历。而是从前一个子字符串的终止点开始遍历。
 这样就避免了重复计算。
 又称为“滑动窗口法”
 */

class Solution {
    public int equalSubstring(String s, String t, int maxCost) {
        int[] dis = new int[s.length()];
        for (int i = 0; i < s.length(); i++) {
            dis[i] = abs(s.charAt(i), t.charAt(i));
        }
        //int[] res = new int[s.length()];
        int max = 0;
        int tmp = 0, left = maxCost;
        boolean flag = false; // 判断是否消费了，如果没有，是不会进行max值判断的。
        for (int i = 0; i < s.length(); i++) {
            if (i != 0) {
                left += dis[i-1];
            }
            while (tmp < s.length() && left >= 0) {
                if (left >= dis[tmp]) {
                    left -= dis[tmp++];
                    flag = true;
                } else {
                    break;
                }
            }
            if (flag && (tmp - i) > max) {
                max = tmp - i;
                flag = false;
            }
            if (tmp == s.length()) {
                return max;
            }
        }
        return max;
    }

    public int abs(char a, char b) {
        if (a < b) {
            return b - a;
        } else {
            return a - b;
        }
    }
}
