/**********************************************
  > File Name		: deleteString.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Oct  2 11:02:44 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int deleteString(string s) {
        int n = s.length();
        if (equal(s.begin() + 1, s.end(), s.begin())) // 特判全部相同的情况
            return n;
        int lcp[n + 1][n + 1]; // lcp[i][j] 表示 s[i:] 和 s[j:] 的最长公共前缀
        memset(lcp, 0, sizeof(lcp));
        for (int i = n - 1; i >= 0; --i)
            for (int j = n - 1; j > i; --j)
                if (s[i] == s[j])
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
        int f[n];
        memset(f, 0, sizeof(f));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; i + j * 2 <= n; ++j)
                if (lcp[i][i + j] >= j) // 说明 s[i:i+j] == s[i+j:i+j*2]
                    f[i] = max(f[i], f[i + j]);
            ++f[i];
        }
        return f[0];
    }
};

class Solution1 {
public:
    int deleteString(string s) {
        const int n = s.size();

        if (n <= 1) return 1;

        vector<int> dp(n, 1);
        map<int, vector<int>> mdp;

        mdp.insert({1, {n-1}});

        auto compare = [&](const int _i, const int l) {
            for (int i = _i; i < _i+l; i++) {
                if (s[i] != s[i+l]) {
                    return false;
                }
            }
            return true;
        };

        for (int i = n-2; i >= 0; i--) {
            printf("\ni = %d, c = %c\n", i, s[i]);
            const int len = n - i;
            bool flag = true;

            for (auto it = mdp.rbegin(); flag && it != mdp.rend(); it++) {
                printf("choice = %d\n", it->first);
                for (const int id: it->second) {
                    const int l = len - n + id;
                    printf("id = %d, l = %d\n", id, l);
                    //if (l % 2) continue;

                    if (compare(i, l)) {
                        printf("equal when l = %d\n", l);
                        const int temp_res = it->first+1;
                        dp[i] = temp_res;

                        if (mdp.find(temp_res) == mdp.end()) {
                            mdp.insert({temp_res, {i}});
                            printf("insert [%d, %d]\n", temp_res, i);
                        } else {
                            mdp[temp_res].push_back(i);
                            printf("%d insert %d\n", temp_res, i);
                        }

                        flag = false;
                    }
                }
            }

            if (flag) {
                printf("delete whole string\n");
                mdp[1].push_back(i);
            }
            //for (int l = 1; l <= (len>>1); l++) {
                //if (compare(i, l)) {
                    //dp[i] = max(dp[i], dp[i+l] + 1);
                //}
            //}
        }
        return dp[0];
    }
};

int main() {
    string s = "ilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkeilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqilqzuvkebqumabhsdwjesovwhqjvphhigtqubeazichenrkipozlnrjpmxojqmonwdwkeyfptfkwcwzyqglgrqoaiufbhcplnrhvljsjqvvcryxfiifzkvdwtrveehprjrycsiljusynfxtgvzhzczqhbmrfutryzguvpmsrsoudxbinfrdwadboontbjjbzbyhextdynmdwhodebxwgcdrvwtttvhuxzqweahbmfecmoawmwunzlltklrcchkvbpkbpfrupkwmbfmbmldefzichboxigbgusfyirfaypemrjqjaprtblyjdyyycqymoxuuwyvbyqeihlysakceywfjqczosimkpkiqyautfymxsgkiagshmdxgsudaijuxcrkbsrcedirltpjhrdozrghtvinqofwomywcharaabfprotzlmfhoxbzbamqypjwrlivyrytehwsmdxpdrlnxdiqagtfmuqvckqabvlmedptfaerixwsnzzzucildclmximjhpkcvvwadzwsquflhznwoeyhtiydbsivhimkynqydfkdjonicpywvtgtmwisetxsyjpuffvkhmdptagagrivjnsabgqoltdypvirauiwgjlupliioletrpthrslwyofyomldadbtqhoczvwczmfcfazncwrsvkotsognwpdcuounqhuhtstfaenrzwmhatnwqzdtqoscuxgxnsavyhplcgqczfamyyzyukfswpnjbyexesuhgmjhzfdrdmcjxcieiejwwenwnwbfxesanttgwarcykrclbzwmyj";
    printf("%d\n", Solution().deleteString(s));
}
