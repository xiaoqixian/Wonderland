/*
 Leetcode: 28.实现strStr()
 本题能够有幸实现空间和时间均击败100%用户 
 */
 
#include <stdio.h>
#include "common.h"
#include <string.h>

void getNext(char* pat, int next[]) {
	int j = 0, k = -1;
	next[0] = -1;
	int len = strlen(pat);
	
	while (j < len - 1) {
		if (k == -1 || pat[j] == pat[k]) {
			k++;
			j++;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
}

int strStr(char* str, char* pat) {
    int str_size = strlen(str), pat_size = strlen(pat);
    if (pat_size == 0) {
        return 0;
    }
    if (str_size < pat_size) {
        return -1;
    }
	int* next = (int*)malloc(sizeof(int) * pat_size);
	getNext(pat, next);
	int j = 0, k = 0;
	while (j < str_size) {
		if (k == -1 || str[j] == pat[k]) {
			j++;
			k++;
		}
		else {
			k = next[k];
		}
		if (k == pat_size) {
            free(next);
			return (j - pat_size);
		}
	}
    free(next);
	return -1;
}

int main() {
	const char* pat = "ABCDABD";
	const char* str = "BBCABCDABABCDABCDABDE";
	printf("%d\n", strStr(str, pat));
	return 0;
}
