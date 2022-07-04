/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Jan 2022 10:26:31 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <iostream>
#include <bitset>

int main() {
    int x = 3;
    std::bitset<32> a(x), b(-x);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << (x & -x) << std::endl;
}
