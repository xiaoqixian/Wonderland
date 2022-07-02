/**********************************************
  > File Name		: FreqStack.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 02 Apr 2022 09:33:28 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stack>
#include <unordered_map>
using namespace std;

class FreqStack {
private:
    stack<int> s, temp;
    int max_freq;
    unordered_map<int, int> value_freq;
public:
    FreqStack() {
        this->s = stack<int>();
        this->temp = stack<int>();
        this->max_freq = 1;
        this->value_freq = unordered_map<int, int>();
    }
    
    void push(int val) {
        this->s.push(val);
        auto freq = this->value_freq.find(val);
        if (freq == this->value_freq.end())
            this->value_freq.insert({val, 1});
        else {
            freq->second++;
            if (freq->second > this->max_freq)
                this->max_freq = freq->second;
        }
    }
    
    int pop() {
        if (this->s.empty())
            return -1;

        int res = -1, second_max_freq = 0;
        bool met = false;
        unordered_map<int, int>::iterator iter;

        while (!this->s.empty()) {
            iter = this->value_freq.find(this->s.top());
            if (!met) {
                if (iter->second == this->max_freq) {
                    met = true;
                    res = iter->first;
                    continue;
                }
                this->temp.push(this->s.top());
                this->s.pop();
                continue;
            }
            if (met && iter->second > second_max_freq)
                second_max_freq = iter->second;
        }

        while (!this->temp.empty()) {
            this->s.push(this->temp.top());
            this->temp.pop();
        }

        this->max_freq = second_max_freq;
        return res;
    }
};

int main() {}

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
