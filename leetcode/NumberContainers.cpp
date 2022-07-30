/**********************************************
  > File Name		: NumberContainers.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 30 15:30:47 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <unordered_map>
#include <map>
#include <queue>

class NumberContainers {
private:
    typedef std::priority_queue<int, std::vector<int>, std::greater<int>> pq_type;
    std::map<int, int> index_map;
    std::unordered_map<int, pq_type> number_index;
public:
    NumberContainers() {

    }

    int get_old(const int index) const {
        auto it = this->index_map.find(index);
        return it == this->index_map.end() ? 0 : it->second;
    }
    
    void change(const int index, const int number) {
        this->index_map[index] = number;
        
        auto it = this->number_index.find(number);
        if (it == this->number_index.end()) {
            pq_type pq;
            pq.push(index);
            this->number_index.insert({number, pq});
        } else {
            it->second.push(index);
        }
    }
    
    int find(const int number) {
        auto it = this->number_index.find(number);
        if (it != this->number_index.end() && !it->second.empty()) {
            pq_type& pq = it->second;
            while (!pq.empty() && this->index_map[pq.top()] != number) {
                pq.pop();
            }

            if (!pq.empty())
                return pq.top();
        }
        return -1;
    }
};

/*
 * 和别人的思想基本一样，但就是时间差了许多。
 */
const int IO_OP=[](){ios::sync_with_stdio(false); cin.tie(nullptr); return 0;}();
class NumberContainers {
public:
    unordered_map<int, int> mp;
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> minv;

    NumberContainers() {

    }
    
    void change(int x, int v) {
        if(mp[x]!=v){
            mp[x]=v;
            minv[v].push(x);
        }
    }
    
    int find(int v) {
        if(minv.count(v)==0) return -1;
        auto& q=minv[v];
        while(!q.empty()){
            auto t=q.top();
            if(mp[t]!=v){
                q.pop();
                continue;
            }
            return t;
        }
        return -1;
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
