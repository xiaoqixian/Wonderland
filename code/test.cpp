/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 04 Feb 2021 10:45:56 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <cstdlib>
#include <cstdio>
using namespace std;

int main() {
    const char* s = "record with key = %d\n";
    char* fs = new char[100];
    int key = 100;
    sprintf(fs, s, key);
    printf(fs);
}
