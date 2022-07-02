/**********************************************
  > File Name		: DinnerPlates.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 03 Apr 2022 02:47:46 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <iostream>
#include <stack>
#include <set>
using namespace std;

class DinnerPlates {
private:
    vector<stack<int>> plates;
    set<int> remain, nonempty;
    int capacity;
public:
    DinnerPlates(int capacity): capacity(capacity) {}
    
    void push(int val) {
        if (this->remain.empty()) {
            this->plates.push_back(stack<int>({val}));
            if (this->capacity > 1)
                this->remain.insert(this->plates.size()-1);
            this->nonempty.insert(this->plates.size()-1);
        } else {
            auto minRemain = this->remain.begin();
            stack<int>& s = this->plates[*minRemain];
            s.push(val);

            if (s.size() == 1) {
                this->nonempty.insert(*minRemain);
            }

            if (s.size() == this->capacity) {
                this->remain.erase(minRemain);
            }
        }
    }
    
    int pop() {
        if (this->nonempty.empty())
            return -1;
        auto maxNonempty = --this->nonempty.end();
        stack<int>& s = this->plates[*maxNonempty];

        int res = s.top(); s.pop();

        if (s.size() == this->capacity-1) {
            this->remain.insert(*maxNonempty);
        }

        if (s.empty()) {
            this->nonempty.erase(maxNonempty);
        }
        return res;
    }
    
    int popAtStack(int index) {
        if (index >= this->plates.size() || this->plates[index].empty())
            return -1;

        stack<int>& s = this->plates[index];
        int res = s.top(); s.pop();

        if (s.size() == this->capacity-1)
            this->remain.insert(index);

        if (s.empty()) {
            this->nonempty.erase(this->nonempty.find(index));
        }
        return res;
    }
};

int main() {
    set<int> s = {4, 6, 1, 2};
    cout << *s.begin() << endl;
    cout << *s.rbegin() << endl;
}

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */
