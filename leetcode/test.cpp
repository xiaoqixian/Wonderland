/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Jan 2022 10:26:31 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4};
    auto start = v.begin(), end = ++start;
    v.erase(start, ++end);

    for (auto n: v) {
        printf("%d, ", n);
    }
    printf("\n");
    cout << "end at " << *end << endl;
    cout << "start at " << *start << endl;
}
