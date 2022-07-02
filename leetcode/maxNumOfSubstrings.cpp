/**********************************************
  > File Name		: maxNumOfSubstrings.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 20 Jul 2020 11:42:02 PM CST
 ************************************************/

#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>

/*
 * Leetcode 1520.最多的不重叠子字符串
 *
 * 首先肯定是要找到所有可能的子字符串，方法就是从左至右对每个字母都查找一次，
 * 对于一个字母，首先找到其在字符串最右边的位置，然后查找在两个范围内所有的
 * 字符的最后一个字符所在位置，最终将最远的位置所谓子字符串的终止位置。
 * 按道理说，每个出现过的字母都值得在map中出现一次。
 */

bool func(vector<int> a, vector<int> b) {
    return a[0] < b[0]; //小的排前面
}
class Solution {
public:
    //定义函数用于vector排序
    vector<string> maxNumOfSubstrings(string s) {
        //printf("string size: %zd\n", s.size());
        //为了避免重复遍历，首先遍历一边所有字符，找到所有字符的开始和结束位置
        vector<vector<int>> chars(26, {-1,-1});
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (chars[c-'a'][0] == -1) {
                chars[c-'a'][0] = i;
                chars[c-'a'][1] = i;
            } else {
                chars[c-'a'][1] = i;
            }
        }
        vector<vector<int>> intervals;
        printf("intervals init size: %zd\n", intervals.size());
        int len = 0;
        bool included = false;
        vector<string> res;
        vector<bool> viewed(26, false);
        int viewedChar = 0;
        //printf("start loop\n");
        for (int i = 0; i < s.size(); i++) {
            if (viewedChar > 26) {
                break;
            }
            //printf("loop\n");
            char c = s[i];
            if (viewed[c - 'a']) {
                continue;
            }
            //首先找到此字符最后一次出现的位置
            int lastIndex = chars[c-'a'][1];
            if (lastIndex == -1) {
                throw "char not found";
            }
            for (int j = i+1; j <= lastIndex; j++) {
                //在中间的字符串中，如果存在字符已经在map中出现过，则应该本子字符串应该已经被包括
                if (viewed[s[j]-'a']) {
                    included = true;
                    break;
                }
                int includeLastIndex = chars[s[j]-'a'][1];
                if (lastIndex < includeLastIndex) {
                    lastIndex = includeLastIndex;
                }
            }
            if (included) {
                included = false;
            }
            else {
                if (len > 25) {
                    throw "intervals out of range";
                }
                //intervals[len++] = {i, lastIndex};
                intervals.push_back({i, lastIndex});
            }
            if (!viewed[c-'a']) {
                viewedChar++;
            }
            viewed[c - 'a'] = true;
            //printf("c: %c\n", c);
        }
        //这样就得到了所有可行子字符串的开始和结束索引
        //printf("intervals size: %zd", intervals.size());
        sort(intervals.begin(), intervals.end(), func);
        //printVector(intervals);
        // 然后区间的比较分为三种情况：后来的不与前面的相交、后来的完全包含于前面的、后来的与前面的部分相交
        // 准备一个stack
        stack<vector<int>> cont;
        for (int i = 0; i < intervals.size(); i++) {
            vector<int> interval = intervals[i];
            if (cont.empty()) {
                cont.push(interval);
                //printf("bottom:[%d, %d]\n", interval[0], interval[1]);
            } else {
                if (interval[0] > cont.top()[1]) {//说明不相交
                    cont.push(interval);
                } else {
                    if (interval[1] < cont.top()[1]) { //说明完全包含
                        cont.pop();
                        cont.push(interval);
                    }
                }
            }
        }
        while (!cont.empty()) {
            vector<int> top = cont.top();
            res.push_back(s.substr(top[0], top[1]-top[0]+1));
            cont.pop();
        }
        return vector(res.rbegin(), res.rend());
    }
};


//上面这个是我可以想到的最快捷的做法了，但是速度上只能击败70%

