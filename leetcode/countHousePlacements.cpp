/**********************************************
  > File Name		: countHousePlacements.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu Aug  4 17:23:34 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;
//int ddl[20000];
class Solution {
private:
    static const int mod = 1e9 + 7;
public:
    int countHousePlacements(const int n) {
        //memset(ddl, 1, 20000*sizeof(int));
        vector<int> ddl(n<<1, 1);
        int res = (n<<1) + 1;
        int prev, curr;
        
        for (int house = 2; house <= n; house++) {
            int last_house_index = (house-1)<<1;
            int base = ddl[last_house_index-2];
            curr = ddl[last_house_index-1];

            while (last_house_index < (n<<1)) {
                prev = curr;
                curr = ddl[last_house_index];

                if (last_house_index == n) {
                    base = (base + prev) % mod;
                    ddl[last_house_index] = base;
                    last_house_index++;
                    continue;
                }

                ddl[last_house_index] = base;
                res = (res + base) % mod;
                base = (base + prev) % mod;
                last_house_index++;
            }
        }
        return res;
    }
};
