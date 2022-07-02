/**********************************************
  > File Name		: customStack.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 24 Oct 2020 11:12:48 PM CST
  > Location        : Shanghai
 **********************************************/

/*
 * Leetcode 1381.设计一个支持增量操作的栈
 * 主要难点在于increment函数，如果才能在O(1)的复杂度下完成这一操作？
 * 我的办法是利用栈的特性：下面的元素永远比上面的元素晚出来
 * 而对于increment函数所增加的值，在一个元素未出栈之前，这些值增加的顺序其实
 * 并不重要，所以只要维护一个数组increases和一个最大增长位置maxIncrease
 * 当位置低于maxIncrease的元素出栈时，就要加上increases[maxIncrease]的增长值
 *
 * 同时，increases[maxIncrease]表示maxIncrease位置以下的所有元素都要增加的值
 * 所以increases[maxIncrease-1] += increases[maxIncrease].
 */

class CustomStack {
private:
    int* stack, *increases;
    int top, max, maxIncrease; //maxIncrease表示最高需要增长的位置
public:
    CustomStack(int maxSize) {
        if (maxSize <= 0) {
            return ;
        }
        stack = new int[maxSize];
        increases = new int[maxSize]();
        top = 0;
        max = maxSize;
        maxIncrease = 0;
    }

    void push(int x) {
        if (top >= max) {
            return ;
        }
        stack[top++] = x;
    }

    int pop() {
        if (top == 0) {
            return -1;
        }
        int increase = 0;
        if (top - 1 == maxIncrease) { //如果最高需要增长的位置位于top
            increase = increases[maxIncrease];
            increases[maxIncrease--] = 0;
            /*
            while (maxIncrease >= 0 && increases[maxIncrease] == 0) {
                maxIncrease--;
            }
            */
            if (maxIncrease >= 0) {
                increases[maxIncrease] += increase;
            } else {
                maxIncrease = 0;
            }
        }
        return stack[--top] + increase;
    }

    void increment(int k, int val) {
        if (top == 0) {
            return ;
        }
        if (k > top) {
            maxIncrease = top - 1;
            increases[maxIncrease] += val;
        } else if (k > maxIncrease) {
            maxIncrease = k - 1;
            increases[maxIncrease] += val;
        } else {
            increases[k - 1] += val;
        }
    }
};
