/**********************************************
  > File Name		: minimumNumbers.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Aug  9 16:03:25 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    int minimumNumbers(const int num, const int k) {
        vector<int> dp(num+1, -1);
        int res = 0, curr = k;

        dp[0] = 0;

        auto produce = [&]() {
            if (!curr) curr += 10;
            if (curr > num) return 0;
            curr += 10;
            return curr-10;
        };

        for (int item = produce(); item; item = produce()) {
            printf("\nitem = %d\n", item);
            dp[item] = 1;
            for (int i = 0; i <= (num-item); i++) {
                //dp[i + item] = dp[i + item] == -1 ? dp[i] + 1 : min(dp[i + item],  dp[i] + 1);
                if (dp[i] != -1)
                    dp[i + item] = dp[i+item] == -1 ? dp[i]+1 : min(dp[i + item], dp[i] + 1);
                //else if (i%item == 0)
                    //dp[i + item] = dp[i] + 1;
                printf("dp[%d] = %d\n", i+item, dp[i+item]);
            }
        }

        return dp[num];
    }
};

int main(int argc, char** argv) {
    printf("%d\n", Solution().minimumNumbers(atoi(argv[1]), atoi(argv[2])));
}
