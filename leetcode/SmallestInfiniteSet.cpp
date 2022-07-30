/**********************************************
  > File Name		: SmallestInfiniteSet.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 23 21:16:26 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <set>
#include <queue>
#include <vector>
using namespace std;

class SmallestInfiniteSet {
private:
    int smallest;
    set<int> popped;
    priority_queue<int, vector<int>, greater<int>> added;
public:
    SmallestInfiniteSet() {
        this->smallest = 1;
    }
    
    int popSmallest() {
        if (!this->added.empty()) {
            int res = this->added.top();
            this->added.pop();
            this->popped.insert(res);
            return res;
        }

        int res = this->smallest;
        this->smallest++;
        this->popped.insert(res);
        return res;
    }
    
    void addBack(int num) {
        if (num >= this->smallest) 
            return;
        auto it = this->popped.find(num);
        if (it != this->popped.end()) {
            this->added.push(*it);
            this->popped.erase(it);
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
