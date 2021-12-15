/**********************************************
  > File Name		: printv.h
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 15 Dec 2021 02:59:00 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#ifndef _PRINTV_H
#define _PRINTV_H

#include <stdio.h>
#include <vector>
using namespace std;

void printv(vector<int>& v) {
    printf("[");
    for (int num: v) {
        printf("%d, ", num);
    }
    printf("]\n");
}

void printv2(vector<vector<int>>& v2) {
    int s1 = v2.size(), s2, i, k;
    if (s1 == 0) {
        printf("[[]]\n");
        return;
    }
    printf("[");
    vector<int>& v = v2[0];
    s2 = v.size();
    if (s2 == 0) {
        printf("[]");
    } else {
        printf("[%d", v[0]);
        for (k = 1; k < s2; k++) {
            printf(", %d", v[k]);
        }
        printf("]");
    }

    for (i = 1; i < s1; i++) {
        printf(",\n");
        vector<int>& v = v2[i];
        s2 = v.size();

        if (s2 == 0) {
            printf("[]");
        } else {
            printf("[%d", v[0]);
            for (k = 1; k < s2; k++) {
                printf(", %d", v[k]);
            }
            printf("]");
        }   
    }
    printf("]\n");
}


#endif /* _PRINTV_H*/
