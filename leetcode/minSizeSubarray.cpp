// Date: Mon Oct 02 14:40:54 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

class RoundNumber {
    int round, value;
public:
    RoundNumber(int round):
        round(round),
        value(0) {}
    RoundNumber(int round, int init):
        round(round),
        value(init) {
        }

    //postfix increment
    int operator++(int) {
        int old = this->value;
        operator++();
        return old;
    }

    int operator++() {
        this->value++;
        this->value %= this->round;
        return this->value;
    }

    operator int() const {
        return this->value;
    }
};

#include <stdio.h>
#include <vector>
int main() {
    RoundNumber rn(10, 0);
    std::vector<int> v = {1,2,3};
    printf("%d\n", v[rn]);
};
