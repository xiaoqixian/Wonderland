/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Jan 2022 10:26:31 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <set>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

void show_set(set<int>& s) {
    if (s.empty()) {
        printf("()\n");
        return;
    }
    set<int>::iterator i;
    for (i = s.begin(), printf("(%d", *i), i++; i != s.end(); i++) {
        printf(", %d", *i);
    }
    printf(")\n");
}

void show_iter(set<int>& s, set<int>::iterator iter) {
    printf("[");
    if (s.empty()) {
        printf("()");
        return;
    }

    if (iter == s.begin()) {
        printf("(), ");
    } else {
        printf("(");
        for (set<int>::iterator temp = s.begin(); temp != iter; temp++) {
            printf("%d, ", *temp);
        }
        printf("), ");
    }

    printf("%d, ", *(iter++));
    
    if (iter == s.end()) {
        printf("()]\n");
    } else {
        printf("(");
        for (; iter != s.end(); iter++) {
            printf("%d, ", *iter);
        }
        printf(")]\n");
    }
}

int add_ss(string a, string b) {
        int res = 0, temp, d = 1; 
        bool carry = false;
        string::reverse_iterator a_iter, b_iter, a_rend = a.rend(), b_rend = b.rend();
        
        for (a_iter = a.rbegin(), b_iter = b.rbegin(); a_iter != a_rend && b_iter != b_rend; a_iter++, b_iter++) {
            printf("a_iter = %c, b_iter = %c\n", *a_iter, *b_iter);
            temp = *a_iter + *b_iter - '0' - '0';
            if (carry) {
                carry = false;
                temp++;
            }

            if (temp > 9) {
                carry = true;
                temp -= 10;
            }
            res += d*temp;
            d *= 10;
        }

        string::reverse_iterator iter, rend;
        if (a_iter != a_rend)
            iter = a_iter, rend = a_rend;
        else
            iter = b_iter, rend = b_rend;

        for (; iter != rend; iter++) {
            temp = *iter - '0';
            if (carry)
                carry = false, temp++;

            if (temp > 9)
                carry = true, temp -= 10;

            res += d*temp;
            d *= 10;
        }

        return res;
    }

int main() {
    printf("%d\n", add_ss("128", "23132"));
}
