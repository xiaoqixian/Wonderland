/**********************************************
  > File Name		: isAdditiveNumber.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 10 Jan 2022 09:48:35 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/**
 * 在前进的过程中可能遇到两种无法匹配的情况：
 * 1. 值无法匹配，这种情况则加数的长度加一后重新压入栈前进
 * 2. 长度无法匹配，由于加法结果的长度必须是两加数的长者的长度或加一
 *    首先看是否是由于被加数a的长度过长，如果是则这轮放弃，什么也不压入。
 *    如果是由于加数b的长度过长，则被加数a长度加一压入，加数b的长度为1
 *    压入。
 */

/**
 * Backtracking algorithm is for sure.
 *
 * For a length n string and a length m string, assume n > m,
 * the result string length should be either n or n+1.
 *
 * We can first calculate the single digit to determine the result's
 * length, if both match, we compare both n and n+1 result string.
 */

#include <stack>
#include <string>
#include <stdio.h>
using namespace std;

void print_stack(stack<int>& s) {
    stack<int> ss = s;
    while (!ss.empty()) {
        printf("%d<-", ss.top());
        ss.pop();
    }
    printf("\n");
}

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int len = num.size(), start = 0;
        if (len < 3) return false;
        stack<int> nums; //store the length of numbers.
        bool res = false;

        nums.push(1), nums.push(1);
        while (!res && !nums.empty()) {
            int b = nums.top(); nums.pop();
            int a = nums.top(); nums.pop(); //we can make sure that a doesn't start with 0

            if (start + a >= len || (num[start] == '0' && a > 1)) {
                if (!nums.empty()) {
                    start -= nums.top(); 
                    nums.push(a + 1);
                }
                continue;
            }

            if (num[start + a] == '0' && b > 1) { //if b starts with 0
                nums.push(a + 1), nums.push(1);
                continue;
            }

            int c = max(a, b), count = min(a, b);

            printf("\na = %d, b = %d, start = %d, c = %d\n", a, b, start, c);

            int remain = c - count;
            int x = start + a - 1, y = start + a + b - 1;// x and y is the indice of the single digit of a and b.

            //c has two cases
            int z1 = start + a + b + c - 1, z2 = z1 + 1;
            bool flag1 = true, flag2 = true, carry = false;
            int temp;

            printf("x = %d, y = %d, z1 = %d\n", x, y, z1);

            //check z1 and z2 index validity
            if (z1 >= len) {
                printf("z1=%d exceeds length\n", z1);
                if (a > (len - start)/3) {
                    printf("a too long\n");
                    if (!nums.empty())
                        start -= nums.top(), nums.push(a + 1); //backtracking.
                } else if (b > (len - start - a)/2)
                    nums.push(a + 1), nums.push(1), printf("b too long\n");
                continue;
            } else if (z2 >= len) {
                flag2 = false;
            }

            //check if c starts with 0
            if (num[start + a + b] == '0') {
                if (c > 1) {
                    nums.push(a), nums.push(b + 1);
                    continue;
                }
                else
                    flag2 = false;
            }

            while (count-- && (flag1 || flag2)) {
                temp = num[x--] + num[y--] - '0' - '0';
                if (carry)
                    temp++, carry = false;
                if (temp > 9)
                    temp -= 10, carry = true;

                printf("temp = %d, carry = %d\n", temp, carry);

                if (flag1 && temp != num[z1--] - '0')
                    flag1 = false;
                if (flag2 && temp != num[z2--] - '0')
                    flag2 = false;
            }

            int i = a > b ? x : y;
            while ((flag1 || flag2) && remain--) {
                temp = num[i--] - '0';
                if (carry)
                    temp++, carry = false;
                if (temp > 9)
                    temp -= 10, carry = true;

                if (flag1 && temp != num[z1--] - '0')
                    flag1 = false;
                if (flag2 && temp != num[z2--] - '0')
                    flag2 = false;
            }

            nums.push(a);
            if (flag1 || flag2) {//means a and b is temporarily right
                nums.push(b);
                int curr_len = start + a + b + c;

                printf("curr_len = %d, len = %d\n", curr_len, len);

                if (flag1 && curr_len == len)
                    res = true;
                else if (flag2 && curr_len+1 == len)
                    res = true;
                start += a;
            } else {
                nums.push(b + 1);
            }

            if (flag1)
                nums.push(c), printf("choose z1\n");
            else if (flag2)
                nums.push(c + 1), printf("choose z2\n");

        }
        return res;
    }
};

int main() {
    Solution s;
    string num = "0101";
    printf("%d\n", s.isAdditiveNumber(num));
}
