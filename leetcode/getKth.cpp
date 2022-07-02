/**********************************************
  > File Name		: getKth.cpp
  > Author			: lunar
  > Mail			: lunar_ubuntu@qq.com
  > Created Time	: Thu 16 Jul 2020 09:46:49 AM CST
 ****************************************/

#include <iostream>
using namespace std;

/*
 Leetcode 1387. 将整数按权重排序
 知识点：优先队列
 记忆化：不用想也知道，在很多个连续数的计算过程中肯定存在大量的重复计算。比较好的解决办法就是记忆化
 建立一个map用来存储已经计算过的数。
 然后通过优先队列进行排序
 */

struct comp {
    int steps;
    int number;
    bool operator< (const struct comp a) const {
        if (steps == a.steps) {
            return number > a.number;//由于是升序排序，当本number大于a的number时，就应该排在后面
        }
        return steps > a.steps;
    }
};

class Solution {
public:
    priority_queue<comp> q;
    int getKth(int lo, int hi, int k) {
        map<int, int> m;
        int weights[hi - lo + 1];
        for (int i = lo; i <= hi; i++) {
            int next;
            if (i & 1) {
                next = 3*i + 1;
            }
            else {
                next = i/2;
            }
            if (m.find(next) == m.end()) {
                int steps = get(next);
                m[next] = steps;
                m[i] = steps + 1;
            }
            else {
                m[i] = m[next] + 1;
            }
        }
        /*
         接下来就是要解决排序的问题,采用优先队列，有两重优先级
         */
        for (int i = lo; i <= hi; i++) {
            struct comp tmp = {m[i], i};
            q.push(tmp);
        }
        while (--k) {
            q.pop();
        }
        struct comp tmp = q.top();
        return tmp.number;
    }

    int get(int k) {
        int res = 0;
        int tmp;
        while (k != 1) {
            if (k % 2 == 0) {
                k /= 2;
                res++;
            }
            else {
                tmp = k;
                k += tmp;
                k += tmp;
                k += 1;
                res++;
            }
        }
        return res;
    }
};
