/**********************************************
  > File Name		: idealArrays.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 23 23:39:34 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <math.h>
#include <unordered_map>
using namespace std;

class Solution {
private:
    const static int mod = 1000000007;
    static unordered_map<uint32_t, int> cache;
public:
    int idealArrays(const int n, const int maxValue) {
        return _idealArrays(n, maxValue);
    }

    int _idealArrays(const int n, const int maxValue) {
        uint32_t key = (((uint32_t)n) << 16) + (uint32_t)maxValue;
        auto it = cache.find(key);
        if (it != cache.end())
            return it->second;

        if (n == 2) {
            int res = 0;
            for (int i = 1; i <= (maxValue>>1); i++) {
                res += (maxValue / i);
            }
            res += (maxValue >> 1) + (maxValue % 2);
            res %= mod;
            cache.insert({key, res});
            return res;
        }
        
        int res = 0;
        for (int t = 1; t <= maxValue; t++) {
            res += _idealArrays(n - 1, maxValue/t);
            res %= mod;
        }
        cache.insert({key, res});
        return res;
    }
};

int main() {}
