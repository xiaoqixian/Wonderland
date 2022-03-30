/**********************************************
  > File Name		: MyCircularDeque.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 30 Mar 2022 11:14:54 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class MyCircularDeque {
private:
    int* array;
    int front, rear, size, capacity;
public:
    MyCircularDeque(int k) {
        this->array = new int[k];
        this->front = 0;
        this->rear = 0;
        this->size = 0;
        this->capacity = k;
    }

    ~MyCircularDeque() {
        delete[] this->array;
    }
    
    bool insertFront(int value) {
        if (this->size == this->capacity)
            return false;

        if (this->front == this->rear) {
            this->array[this->front] = value;
            if (this->rear == this->capacity - 1)
                this->rear = 0;
            else this->rear++;
            this->size++;
            return true;
        }

        if (this->front == 0) {
            this->front = this->capacity-1;
        }
        else {
            this->front--;
        }
        this->array[this->front] = value;
        this->size++;
        return true;
    }
    
    bool insertLast(int value) {
        if (this->size == this->capacity)
            return false;
        
        if (this->front == this->rear) {
            this->array[this->front] = value;
            if (this->rear == this->capacity - 1)
                this->rear = 0;
            else this->rear++;
            this->size++;
            return true;
        }

        this->array[this->rear] = value;
        this->size++;

        if (this->rear == this->capacity - 1)
            this->rear = 0;
        else this->rear++;
        return true;
    }
    
    bool deleteFront() {
        if (this->size == 0) 
            return false;

        this->size--;
        if (this->front == this->capacity - 1)
            this->front = 0;
        else this->front++;
        return true;
    }
    
    bool deleteLast() {
        if (this->size == 0)
            return false;

        this->size--;
        if (this->rear == 0)
            this->rear = this->capacity - 1;
        else this->rear--;
        return true;
    }
    
    int getFront() {
        if (this->size == 0)
            return -1;
        return this->array[this->front];
    }
    
    int getRear() {
        if (this->size == 0)
            return -1;
        if (this->rear == 0)
            return this->array[this->capacity-1];
        else return this->array[this->rear - 1];
    }
    
    bool isEmpty() {
        return this->size == 0;
    }
    
    bool isFull() {
        return this->size == this->capacity;
    }
};

#include <iostream>
using namespace std;
int main() {
    MyCircularDeque dq(3);
    dq.insertLast(1);
    dq.insertLast(2);
    dq.insertFront(3);
    cout << dq.insertFront(4) << endl;
    cout << dq.getRear() << endl;
}

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
