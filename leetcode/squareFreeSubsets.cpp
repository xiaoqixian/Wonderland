/**********************************************
  > File Name		: squareFreeSubsets.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Feb 20 23:24:23 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <numeric>

class Solution {
    static constexpr int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    static constexpr int MOD = 1e9 + 7, MX = 30, N_PRIMES = 10, M = 1 << N_PRIMES;
public:
    int squareFreeSubsets(std::vector<int> &nums) {
        int nsq2mask[MX + 1]{}; // nsq2mask[i] 为 i 对应的质数集合（用二进制表示）
        for (int i = 2; i <= MX; ++i)
            for (int j = 0; j < N_PRIMES; ++j) {
                int p = PRIMES[j];
                if (i % p == 0) {
                    if (i % (p * p) == 0) { // 有平方因子
                        nsq2mask[i] = -1;
                        break;
                    }
                    nsq2mask[i] |= 1 << j; // 把 j 加到集合中
                }
            }

        int f[M]{1}; // f[j] 表示恰好组成集合 j 的方案数，其中空集的方案数为 1
        for (int x : nums)
            if (int mask = nsq2mask[x]; mask >= 0) // x 是 NSQ
                for (int j = M - 1; j >= mask; --j)
                    if ((j | mask) == j)  // mask 是 j 的子集
                        f[j] = (f[j] + f[j ^ mask]) % MOD; // 不选 mask + 选 mask
        return (std::accumulate(f, f + M, 0L) - 1) % MOD; // -1 去掉空集
    }
};

