/**********************************************
  > File Name		: takeCharacters.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu Jan 19 17:05:29 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int takeCharacters(string s, int k) {
        vector<int> space(3, 0);
        const int n = s.size();
        int right = n;
        auto valid = [&]() {
            return space[0] >= k && space[1] >= k && space[2] >= k;
        };

        while (right >= 0 && !valid()) {
            space[s[--right] - 'a']++;
        } 
        printf("right = %d\n", right);
        if (!valid()) return -1;
        int res = n - right;

        for (int left = 0; left < right; left++) {
            printf("left = %d,", left);
            space[s[left]-'a']++;
            printf(" right %d jump to ", right);
            while (right < n && valid()) {
                space[s[right++]-'a']--;
            }
            printf("%d\n", right);
            if (right == n && valid()) return res;
            space[s[--right]-'a']++;
            res = min(res, left + n - right + 1);
        }
        printf("fuck\n");
        return res;
    }
};

int main() {
    printf("%d\n", Solution().takeCharacters("aabaaaacaabc", 2));
}
