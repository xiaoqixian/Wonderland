# !/usr/bin/python3
# -*- coding: utf-8 -*-
# > Author          : lunar
# > Email           : lunar_ubuntu@qq.com
# > Created Time    : Fri 07 Jan 2022 04:20:10 PM CST
# > Location        : Shanghai
# > Copyright@ https://github.com/xiaoqixian

from typing import List
from heapq import heappop, heappush

# 你有 k 个服务器，编号为 0 到 k-1
# 你的任务是找到 最繁忙的服务器 。最繁忙定义为一个服务器处理的请求数是所有服务器里最多的。
# 1882. 使用服务器处理任务

class Solution:
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:
        busy = []
        free = list(range(k))
        res = [0] * k
        for i, start in enumerate(arrival):
            print("\nprocess time %d i %d" % (start, i))
            print("busy: ", busy)
            print("free: ", free)
            while busy and busy[0][0] <= start:
                _, id = heappop(busy)
                heappush(free, i + (id - i % k) % k) # i%k 为最合适编号，id - i%k 为当前server id 到x
                # i % k + (id - i) % k = id
                # 确保距离 i % k 越近的值越小，最大的应该是 id = i-1, 当id = i-1时，num = i + k-1, 当id = 
            print("busy: ", busy)
            print("free: ", free)
            if free:
                id = heappop(free) % k
                heappush(busy, (start + load[i], id))
                res[id] += 1
            print("busy: ", busy)
            print("free: ", free)

        m = max(res)
        return [i for i in range(k) if res[i] == m]

if __name__ == "__main__":
    s = Solution()
    # k = 3
    # arrival = [1,2,3,4,5]
    # load = [5,2,3,3,3]
    k = 11
    arrival = [5,6,12,14,19,21,25,29,46,49,56,57,58,63,71,72,76,77,79,80,85,90,106,108,109,111,112,116,125,135,142,143,159,160,162,164,166,167,172,173,177,179,183,185,193,196,212,213,226,242,244,245,256,258,263,266,272,274,296,298,311,312,318,320]
    load = [10,50,2,29,9,43,2,46,28,46,56,30,37,4,61,11,25,62,50,31,42,50,11,60,54,57,12,62,8,32,61,62,62,44,64,41,36,55,5,46,52,64,1,41,58,50,46,4,21,10,48,38,33,43,55,28,20,32,26,12,28,33,13,32]
    k = 13
    arrival = [1,3,6,7,8,9,10,14,16,20,21,24,25,28,29,30,33,34]
    load = [20,27,27,14,14,9,15,8,23,1,34,2,28,25,7,6,24,15]
    print(s.busiestServers(k, arrival, load))
