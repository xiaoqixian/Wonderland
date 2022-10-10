/**********************************************
  > File Name		: test.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 06 Jan 2022 10:26:31 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

int main() {
    vector<int> a = {1,2,3,4}, b(4);

    std::transform(a.cbegin(), a.cend(), b.begin(), [](int x) {return x+1;});
    printf("%d\n", b[0]);
}
