/**********************************************
  > File Name		: RandomizedSet.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 17:54:00 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <list>
using namespace std;

class RandomizedSet {
private:
    vector<list<int>> buckets;
    static const int bucketCapacity = 16;
    int bucketSize, size;
public:
    RandomizedSet() {
        this->buckets = vector<list<int>>(bucketCapacity, list<int>());
        this->bucketSize = 0;
        this->size = 0;
    }

    bool insert(int val) {
        int index = val % bucketCapacity;
        list<int>& b = this->buckets[index];

        if (b.empty()) {
            b.push_back(val);
            this->bucketSize++;
            this->size++;
            return true;
        }

        if (val < b.front()) {
            b.push_front(val);
            this->size++;
            return true;
        }

        list<int>::iterator right = b.begin();

        while (right != b.end() && val > *right)
            right++;

        if (right != b.end() && *right == val)
            return false;

        b.insert(right, val);
        this->size++;
        return true;
    }

    bool remove(int val) {
        int index = val & bucketCapacity;
        list<int>& b = this->buckets[index];

        if (b.empty())
            return false;

        if (b.size() == 1) {
            if (b.front() == val) {
                b.pop_front();
                this->size--;
                return true;
            } else return false;
        }

        auto left = b.begin(), right = b.end();
        if (b.size() % 2)
            right--;
        while (left != right) {
            if (*left == val) {
                b.erase(left);
                this->size--;
                return true;
            }

            if (right != b.end() && *right == val) {
                b.erase(right);
                this->size--;
                return true;
            }

            left++; right--;
        }
        return false;
    }

    int getRandom() {
        int count = (rand() % this->size) + 1, index = 0;
        while (1) {
            auto& b = this->buckets[index++];
            if (count > b.size())
                count -= b.size();
            else {
                auto it = b.begin();
                while (--count) it++;

                return *it;
            }
        }
        return -1;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
