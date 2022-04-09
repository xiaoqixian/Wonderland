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
#include <list>
#include <vector>
#include <set>
using namespace std;

int main() {
    set<int> s = {1,2,3,4};
    printf("%d\n", s.erase(2));
}
