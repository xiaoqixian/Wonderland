/**********************************************
  > File Name		: buisiestServer.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 05 Jan 2022 09:40:27 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#include "printv.h"
#include <cassert>
using namespace std;

/*template <typename T>*/
/*class priority_queue {*/
/*private:*/
    /*vector<T> inner;*/
    /*int alloc;*/

/*public:*/
    /*void swim(int k) {*/
        /*while (k > 1 && this->comp(k, k/2)) {*/
            /*this->exch(k, k/2);*/
            /*k /= 2;*/
        /*}*/
    /*}*/

    /*int sink(int k) {*/
        /*int j;*/

        /*while (k<<1 <= this->alloc) {*/
            /*j = k<<1;*/
            /*if (j < this->alloc && this->comp(j+1, j))*/
                /*j++;*/
            /*if (!this->comp(j, k))*/
                /*break;*/
            /*this->exch(j, k);*/
            /*k = j;*/
        /*}*/
        /*return k;*/
    /*}*/

    /*priority_queue() {*/
        /*this->inner = vector<pair<int, int>>();*/
        /*this->alloc = 0;*/
    /*}*/

    /*priority_queue(int k) {*/
        /*this->inner = vector<pair<int, int>>(k+1, make_pair(0, 0));*/
        /*this->alloc = k;*/
        /*for (int i = 1; i <= k; i++) {*/
            /*this->inner[i].second = i-1;*/
        /*}*/
    /*}*/

    /*pair<int, int> operator[](int index) {*/
        /*if (index >= this->alloc) {*/
            /*printf("index %d exceeds size %d\n", index, this->alloc);*/
            /*return make_pair(-1, -1);*/
        /*}*/

        /*return this->inner[index];*/
    /*}*/

    /*pair<int, int> pop() {*/
        /*if (this->inner.size() == 0) {*/
            /*return make_pair(-1, -1);*/
        /*}*/

        /*pair<int, int> res = this->inner[1];*/
        /*this->exch(1, this->inner.size());*/
        /*this->inner.pop_back();*/
        /*this->sink(1);*/
        /*return res;*/
    /*}*/

    /*void push(int i, int k) {*/
        /*pair<int, int> item = make_pair(i, k);*/
        /*if (this->inner.empty()) {*/
            /*this->inner.push_back(item);*/
        /*}*/

        /*this->inner.push_back(item);*/
        /*this->alloc++;*/
        /*this->swim(this->alloc);*/
    /*}*/

    /*void reassign(int k) {*/
        /*if (k >= this->alloc) {*/
            /*printf("index %d exceedsd size %d\n", k, this->alloc);*/
            /*return;*/
        /*}*/

    /*}*/

    /*void exch(int i, int k) {*/
        /*pair<int, int> temp = this->inner[i];*/
        /*this->inner[i] = this->inner[k];*/
        /*this->inner[k] = temp;*/
    /*}*/

    /*bool comp(int i, int k);*/
/*};*/

/*template <>*/
/*bool priority_queue<int>::comp(int i, int k) {*/
    /*return this->inner[i] < this->inner[k];*/
/*}*/

/*template <>*/
/*bool priority_queue<pair<int, int>>::comp(int i, int k) {*/
    /*return this->inner[i].first < this->inner[k].first;*/
/*}*/

class Compare1 {
public:
    bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.first > rhs.first;
    }
};

class Compare2 {
public:
    bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.second > rhs.second;
    }
};

struct Node {
public:
    int val;
    Node* next;
    Node* prev;
    Node(int val): val(val), next(nullptr), prev(nullptr) {}

    void link(Node* node) {
        node->next = this->next;
        node->prev = this;
        this->next = node;
        if (node->next != nullptr) {
            node->next->prev = node;
        }
    }

    void link_prev(Node* node) {
        node->prev = this->prev;
        node->next = this;
        this->prev = node;
        if (node->prev != nullptr) {
            node->prev->next = node;
        }
    }

    //remove next node and free
    void remove() {
        if (this->next == nullptr)
            return;
        Node* temp = this->next;
        this->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = this;
        }
        delete(temp);
    }
};

class list {
public:
    Node* head;
    Node* end;
    list() {
        this->head = nullptr;
        this->end = nullptr;
    }

    void push_back(int val) {
        if (this->head == nullptr) {
            this->head = new Node(val);
            this->end = this->head;
            return;
        }
        this->end->next = new Node(val);
        this->end->next->prev = this->end;
        this->end = this->end->next;
    }

    bool empty() {
        return this->head == nullptr;
    }

    void show() {
        if (this->head == nullptr) {
            printf("empty list\n");
            return;
        }
        printf("%d", this->head->val);
        Node* temp = this->head->next;
        while (temp != nullptr) {
            printf("->%d", temp->val);
            temp = temp->next;
        }
        printf("\n");
    }
};

template <typename T>
void show_pq(const priority_queue<pair<int, int>, vector<pair<int, int>>, T>& pq) {
    if (pq.empty()) {
        printf("empty priority_queue\n");
        return;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, T> cp = pq;
    pair<int, int> entry;
    if (!cp.empty()) {
        entry = cp.top();
        printf("(%d, %d)", entry.first, entry.second);
        cp.pop();
    }

    while (!cp.empty()) {
        entry = cp.top();
        printf("->(%d, %d)", entry.first, entry.second);
        cp.pop();
    }
    printf("\n");
}

void show_set(set<int>& s) {
    if (s.empty()) {
        printf("()\n");
        return;
    }
    set<int>::iterator i;
    for (i = s.begin(), printf("(%d", *i), i++; i != s.end(); i++) {
        printf(", %d", *i);
    }
    printf(")\n");
}


class Solution {
public:
    vector<int> busiestServers1(int k, vector<int>& arrival, vector<int>& load) {
        vector<pair<int, int>> server_loads = vector<pair<int, int>>(k, make_pair(0, 0));
        vector<int> server_finishes = vector<int>(k, 0);
        int n = arrival.size();

        for (int i = 0; i < n; i++) {
            int index = i % k, t = index, time = arrival[i];
            int tsp = server_loads[index].first, server_load = server_loads[index].second;
            while (tsp + server_load > time) {
                ++t %= k;
                if (t == index)
                    break;
                tsp = server_loads[t].first, server_load = server_loads[t].second;
            }

            if (t == index) //can't find an avaliable server
                continue;

            server_loads[t] = make_pair(time, load[i]);
            server_finishes[t]++;
        }

        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_finishes[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_finishes[i];
            } else if (server_finishes[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }

    vector<int> busiestServers2(int k, vector<int>& arrival, vector<int>& loads) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare1> busy;
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare2> holds;
        list avaliable;
        bool flag = true;
        vector<int> server_loads(k, 0);

        for (int i = 0; i < k; i++) {
            //if (flag && k > 50 && i > k/2) {
                //half = avaliable.crbegin();
                //flag = false;
            //}
            avaliable.push_back(i);
        }

        avaliable.show();

        int size = arrival.size();
        for (int i = 0; i < size; i++) {
            int time = arrival[i], load = loads[i], index = i % k;
            printf("\nprocess time %d, load %d, i %d, index %d\n", time, load, i, index);

            printf("busy: "); show_pq(busy); printf("holds: "); show_pq(holds);
            bool added = false;
            if (!busy.empty()) {
                pair<int, int> front = busy.top();
                while (!busy.empty() && time >= front.first) {
                    if (front.second == index) {
                        server_loads[index]++;
                        printf("find from holds\n");
        printf("%d recv at %d, server_loads: ", __LINE__, index); printv(server_loads);
                        added = true;
                        busy.pop();
                        busy.push(make_pair(time + load, index));
                        break;
                    }

                    holds.push(front);
                    busy.pop();
                    front = busy.top();
                }
            }

            if (added)
                continue;
            printf("busy: "); show_pq(busy); printf("holds: "); show_pq(holds);

            printf("1. avaliable list: "); avaliable.show();
            pair<int, int> front;
            Node* temp = avaliable.head;
            bool flag = true;
            if (!holds.empty()) {
                if (temp == nullptr) { //avaliable is empty
                    while (!holds.empty()) {
                        front = holds.top();
                        if (front.second >= index) {
                            server_loads[front.second]++;
        printf("%d recv at %d, server_loads: ", __LINE__, front.second); printv(server_loads);
                            added = true;
                            busy.push(make_pair(time + load, front.second));
                            holds.pop();
                            break;
                        }
                        avaliable.push_back(front.second);
                        holds.pop();
                    }
                } else {
                    front = holds.top();
                    while (!holds.empty() && temp->val > front.second) {
                        if (front.second >= index) {
                            server_loads[front.second]++;
        printf("%d recv at %d, server_loads: ", __LINE__, front.second); printv(server_loads);
                            added = true;
                            busy.push(make_pair(time + load, front.second));
                            holds.pop();
                            break;
                        }

                        Node* new_node = new Node(front.second);
                        if (flag) {
                            avaliable.head = new_node;
                            temp->prev = new_node;
                            new_node->next = temp;
                            flag = false;
                        } else {
                            assert(temp->prev->val < front.second);
                            temp->prev->next = new_node;
                            new_node->next = temp;
                            temp->prev = new_node;
                        }
                        
                        holds.pop();
                        if (holds.empty()) {
                            front.second = -1;
                            break;
                        }
                        front = holds.top();
                    }
                }
            }

            if (added)
                continue;

            printf("2. avaliable list: "); avaliable.show();
            int recv_server = -1;
            flag = true;
            while (temp != nullptr) {
                if (flag && index < temp->val && temp->prev != nullptr && index < temp->prev->val) {
                    printf("%d can't be after %d cause before %d is %d\n", index, temp->val, temp->val, temp->prev->val);
                    break;
                }
                flag = false;
                printf("temp = %d\n", temp->val);

                //if front.second is between temp->val and temp->next->val, insert it.
                if (temp->val < front.second && (temp->next == nullptr ? true : temp->next->val > front.second)) {
                    //printf("add %d to list\n", front.second);
                    Node* new_node = new Node(front.second);
                    new_node->next = temp->next;
                    temp->next = new_node;
                    new_node->prev = temp;
                    if (new_node->next != nullptr)
                        new_node->next->prev = new_node;

                    holds.pop();
                    if (holds.empty())
                        front.second = -1;
                    else
                        front = holds.top();
                }
                
                if (temp->val >= index) {
                    recv_server = temp->val;

                    if (temp->prev == nullptr) {
                        avaliable.head = temp->next;
                    } else {
                        temp->prev->next = temp->next;
                    }

                    if (temp->next == nullptr) {
                        avaliable.end = temp->prev;
                    } else {
                        temp->next->prev = temp->prev;
                    }

                    delete(temp);
                    break;
                }

                temp = temp->next;
            }
            printf("3. avaliable list: "); avaliable.show();

            if (recv_server == -1) {
                if (avaliable.head == nullptr) {
                    printf("time %d, load %d, i %d, index %d skipped\n", time, load, i, index);
                    continue;
                } else {
                    recv_server = avaliable.head->val;
                    temp = avaliable.head;
                    avaliable.head = avaliable.head->next;
                    if (temp->next != nullptr) {
                        temp->next->prev = nullptr;
                    }
                    delete(temp);
                }
            } 
            
            printf("4. avaliable list: "); avaliable.show();
            server_loads[recv_server]++;
        printf("%d recv at %d, server_loads: ", __LINE__, recv_server); printv(server_loads);
            busy.push(make_pair(time + load, recv_server));
        }

        printf("\nserver_loads: "); printv(server_loads);
        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_loads[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_loads[i];
            } else if (server_loads[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }

    //this time I'm gonna use ordered set
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& loads) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare1> busy;
        vector<int> server_loads(k, 0);
        set<int> avaliable;
        set<int>::iterator iter;
        int size = arrival.size();

        for (int i = 0; i < k; i++) {
            avaliable.insert(i);
        }
        
        for (int i = 0; i < size; i++) {
            int time = arrival[i], load = loads[i], index = i % k;
            pair<int, int> front;

            printf("\nprocess time %d, load %d, index %d, i %d\n", time, load, index, i);
            printf("busy before: "); show_pq(busy);
            while (!busy.empty() && (front = busy.top()).first <= time) {
                avaliable.insert(front.second);
                busy.pop();
            }
            printf("busy after: "); show_pq(busy);

            printf("avaliable: "); show_set(avaliable);
            if (avaliable.empty()) {
                printf("this round skipped\n");
                continue;
            }
            set<int>::reverse_iterator riter = avaliable.rbegin();
            if (*riter < index) {
                iter = avaliable.begin();
                server_loads[*iter]++;
                busy.push(make_pair(time + load, *iter));
                avaliable.erase(iter);

                printf("find from begin %d\n", *iter);
                continue;
            }
            for (iter = avaliable.begin(); iter != avaliable.end(); iter++) {
                if (*iter >= index) {
                    server_loads[*iter]++;
                    busy.push(make_pair(time + load, *iter));
                    avaliable.erase(iter);

                    printf("find avaliable %d\n", *iter);
                    break;
                }
            }
        }

        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_loads[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_loads[i];
            } else if (server_loads[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    //vector<int> arrival = {1,2,3,4}, load = {1,2,1,2};
    //vector<int> arrival = {1,2,3,4,5}, load = {5,2,3,3,3};
    //vector<int> arrival = {1,3,4,5,6,11,12,13,15,19,20,21,23,25,31,32};
    //vector<int> load = {9,16,14,1,5,15,6,10,1,1,7,5,11,4,4,6};
    //vector<int> arrival = {1,3,6,7,8,9,10,14,16,20,21,24,25,28,29,30,33,34};
    //vector<int> load = {20,27,27,14,14,9,15,8,23,1,34,2,28,25,7,6,24,15};
    vector<int> arrival = {5,6,12,14,19,21,25,29,46,49,56,57,58,63,71,72,76,77,79,80,85,90,106,108,109,111,112,116,125,135,142,143,159,160,162,164,166,167,172,173,177,179,183,185,193,196,212,213,226,242,244,245,256,258,263,266,272,274,296,298,311,312,318,320};
    vector<int> load = {10,50,2,29,9,43,2,46,28,46,56,30,37,4,61,11,25,62,50,31,42,50,11,60,54,57,12,62,8,32,61,62,62,44,64,41,36,55,5,46,52,64,1,41,58,50,46,4,21,10,48,38,33,43,55,28,20,32,26,12,28,33,13,32};
    Solution s;
    vector<int> res = s.busiestServers(11, arrival, load);
    printv(res);
}
