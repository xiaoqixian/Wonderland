/*
 这题用堆来做真是再合适不过了。对于小顶堆来说，其它位置的顺序可以不在意，但是可以保证根节点的元素一定是
 堆中最小的。
 所以我们就可以直接构建一个小顶堆。
 */

class SortedStack {
private:
    int size;
    int length;
    int count;
    int* s;
    void expand() {
        if (length < size) {
            return ;
        }
        //printf("expand\n");
        int* new_stack = (int*)malloc(sizeof(int) * (size<<1));
        memcpy(new_stack, s, length*sizeof(int));
        free(s);
        s = new_stack;
        size <<= 1;
    }
public:
    SortedStack() {
        size = 8;
        length = 0;
        count = 1;
        s = (int*)malloc(sizeof(int)*size);
        s[length++] = -9090;
    }

    inline void exchange(int i, int j) {
        int tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }

    void swim(int k) {
        while (k > 0 && s[k] < s[k/2]) {
            exchange(k, k/2);
            k /= 2;
        }
    }

    void sink(int k) {
        int j = 2*k;
        while (j < length && s[j] < s[k]) {
            if (j >= length) {
                break;
            }
            if (j < length - 1 && s[j] > s[j+1]) j++;
            //printf("j = %d, k = %d, length = %d\n",j,k, length);
            exchange(j, k);
            k = j;
            j = 2*k;
        }
        if (j < length - 1 && s[j+1] < s[k]) {
            exchange(j+1, k);
        }
    }
    
    void push(int val) {
        printf("%d.push %d\n", count++, val);
        if (length == size) {
            expand();
        }
        s[length++] = val;
        swim(length-1);
        printStack();
    }
    
    void pop() {
        if (length <= 1) {
            printf("%d.pop nothing\n", count++);
            return ;
        }
        printf("%d.pop %d\n",count++, s[1]);
        exchange(1, length-1);
        length--;
        sink(1);
        printStack();
    }
    
    int peek() {
        if (length <= 1) {
            //printf("%d.peek null\n", count++);
            return -1;
        }
        //printf("%d.peek %d\n",count++, s[0]);
        return s[1];
    }
    
    bool isEmpty() {
        //printf("%d.is empty\n", count++);
        return length <= 1 ? 1:0;
    }

    void printStack() {
        printf("[");
        for (int i = 0; i < length; i++) {
            printf("%d ", s[i]);
        }
        printf("]\n");
    }
};

/**
 * Your SortedStack object will be instantiated and called as such:
 * SortedStack* obj = new SortedStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->isEmpty();
 */
