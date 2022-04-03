/**********************************************
  > File Name		: AllOne.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 02 Apr 2022 07:12:24 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <cstdio>
#include <unordered_map>
#include <set>
#include <string>
#include <map>
#include <iostream>
using namespace std;

class AllOne {
private:
    map<int, set<string>> count_map;
    unordered_map<string, int> string_count;


    void showStringCount() {
        cout << "{";
        for (auto iter = this->string_count.begin(); iter != this->string_count.end(); iter++) {
            cout << "{" << iter->first << ": " << iter->second << "}";
        }
        cout << "}" << endl;
    }

    void showCountMap() {
        cout << "{";
        for (auto iter = this->count_map.begin(); iter != this->count_map.end(); iter++) {
            cout << "{" << iter->first << ": [";
            for (auto st = iter->second.begin(); st != iter->second.end(); st++) {
                cout << *st << ", ";
            }
            cout << "}";
        }
        cout << "}" << endl;
    }
public:
    AllOne() {
        this->count_map = map<int, set<string>>();
        this->string_count = unordered_map<string, int>();
    }
    
    void inc(string key) {
        auto find = this->string_count.find(key);
        int count = 0;
        
        if (find == this->string_count.end()) {
            this->string_count.insert({key, 1});
        } else {
            count = find->second;
            this->string_count.insert({key, count+1});
        }

        auto count_set = this->count_map.find(count);
        if (count_set != this->count_map.end()) {
            count_set->second.erase(key);
        }
        
        count_set = this->count_map.find(++count);
        if (count_set == this->count_map.end()) {
            this->count_map.insert({count, {key}});
        } else {
            count_set->second.insert(key);
        }
    }
    
    void dec(string key) {
        auto find = this->string_count.find(key);
        if (find == this->string_count.end())
            return;

        int count = find->second;

        if (count == 1)
            this->string_count.erase(find);
        else
            this->string_count.insert({key, count - 1});

        auto count_set = this->count_map.find(count);
        count_set->second.erase(key);
        if (count_set->second.empty())
            this->count_map.erase(count_set);

        count_set = this->count_map.find(--count);
        if (count_set == this->count_map.end()) {
            this->count_map.insert({count, {key}});
        } else {
            count_set->second.insert(key);
        }
    }
    
    string getMaxKey() {
        if (this->string_count.empty())
            return "";

        auto max_count_set = this->count_map.rbegin()->second;
        return *max_count_set.begin();
    }
    
    string getMinKey() {
        if (this->string_count.empty())
            return "";

        auto min_count_set = this->count_map.begin()->second;
        return *min_count_set.begin();
    }
};

int main() {

}

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
