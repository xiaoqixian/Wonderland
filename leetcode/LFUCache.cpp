/**********************************************
  > File Name		: LFUCache.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 24 Mar 2022 04:49:53 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;

class LFUCache {
private:
    struct Entry {
        int key;
        int value;
        size_t getTimes;
        int latestTime;
        
        Entry(int key, int value, int time): key(key), value(value), getTimes(1), latestTime(time) {}

        //bool operator < (Entry* e2) const {
            //if (this->getTimes != e2->getTimes)
                //return this->getTimes < e2->getTimes;
            //else
                //return this->latestTime < e2->latestTime;
        //}
    };

    struct cmp {
        bool operator() (Entry* const& e1, Entry* const& e2) const {
            return e1->getTimes == e2-> getTimes ? e1->latestTime < e2->latestTime : e1->getTimes < e2->getTimes;
        }
    };

    set<Entry*, cmp> cache;
    unordered_map<int, Entry*> exists;
    int alloc;
    int capacity;
    int time;
public:
    LFUCache(int capacity):
        cache(set<Entry*, cmp>()),
        exists(unordered_map<int, Entry*>()),
        alloc(0),
        time(0),
        capacity(capacity) {}
    
    int get(int key) {
        auto res = this->exists.find(key);
        if (res == this->exists.end())
            return -1;
        else {
            res->second->getTimes++;
            res->second->latestTime = this->time++;
            return res->second->value;
        }
    }
    
    void put(int key, int value) {
        auto res = this->exists.find(key);
        if (res == this->exists.end()) { // put new pair
            if (this->alloc == this->capacity) { // cache full
                auto first = this->cache.begin();
                this->exists.erase(this->exists.find((*first)->key));
                this->cache.erase(first);
                delete *first;
                this->alloc--;
            }

            Entry* newEntry = new Entry(key, value, this->time++);
            this->exists.insert({key, newEntry});
            this->cache.insert(newEntry);
            this->alloc++;
        } else {
            res->second->value = value;
            res->second->getTimes++;
            res->second->latestTime = this->time++;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main() {
    LFUCache* cache = new LFUCache(2);
    cache->put(1,1);
    cache->put(2, 2);
    cache->get(1);
    cache->put(3, 3);
    cout << cache->get(2) << endl;
    cout << cache->get(1) << endl;
}
