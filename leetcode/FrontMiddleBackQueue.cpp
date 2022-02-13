/**********************************************
  > File Name		: FrontMiddleBackQueue.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 13 Feb 2022 02:01:00 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <queue>
using namespace std;

class FrontMiddleBackQueue {
private:
    deque<int> front, back;
public:
    FrontMiddleBackQueue() {
        this->front = deque<int>();
        this->back = deque<int>();
    }

    void print() {
        deque<int> f = this->front, b = this->back;
        printf("[");
        while (!f.empty()) {
            printf("%d, ", f.front());
            f.pop_front();
        }
        printf("| , ");
        while (!b.empty()) {
            printf("%d, ", b.front());
            b.pop_front();
        }
        printf("]\n");
    }
    
    void pushFront(int val) {
        this->front.push_front(val);
    }
    
    void pushMiddle(int val) {
        int f = this->front.size(), b = this->back.size();
        int mid = (f + b)/2, temp;
        if (mid > f) {
            temp = mid - f;
            while (temp--) {
                this->front.push_back(this->back.front());
                this->back.pop_front();
            }
            this->back.push_front(val);
        } else {
            temp = f - mid;
            while (temp--) {
                this->back.push_front(this->front.back());
                this->front.pop_back();
            }
            this->front.push_back(val);
        }
        this->print();
    }
    
    void pushBack(int val) {
        this->back.push_back(val);
    }
    
    int popFront() {
        int res;
        if (this->front.empty()) {
            if (this->back.empty()) {
                return -1;
            } else {
                res = this->back.front();
                this->back.pop_front();
                return res;
            }
        }
        res = this->front.front();
        this->front.pop_front();
        return res;
    }
    
    int popMiddle() {
        int f = this->front.size(), b = this->back.size();
        if (!f && !b) return -1;
        int mid = (f + b)/2, temp;
        if ((f+b) % 2 == 0) mid--;
        if (mid >= f) {
            temp = mid - f;
            while (temp--) {
                this->front.push_back(this->back.front());
                this->back.pop_front();
            }
            temp = this->back.front();
            this->back.pop_front();
        } else {
            temp = f - mid - 1;
            while (temp--) {
                this->back.push_front(this->front.back());
                this->front.pop_back();
            }
            temp = this->front.back();
            this->front.pop_back();
        }
        return temp;
    }
    
    int popBack() {
        int res;
        if (this->back.empty()) {
            if (this->front.empty())
                return -1;
            else {
                res = this->front.back();
                this->front.pop_back();
                return res;
            }
        }
        res = this->back.back();
        this->back.pop_back();
        return res;
    }
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
