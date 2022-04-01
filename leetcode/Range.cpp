/**********************************************
  > File Name		: Range.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 30 Mar 2022 02:21:01 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <iostream>
#include <set>
#include <stdio.h>
using namespace std;

class RangeModule {
private:
    struct Range {
        int left, right;
        Range(int left, int right): left(left), right(right) {}
        Range(set<Range>::iterator iter): left(iter->left), right(iter->right) {}

        bool operator< (const Range& rhs) const {
            return this->left < rhs.left;
        }

        inline bool overlap(const Range& rhs) const {
            if (this->left > rhs.right || this->right < rhs.left)
                return false;
            return true;
        }

        inline bool in(const Range& rhs) const {
            return this->left >= rhs.left && this->right <= rhs.right;
        }

        inline bool include(const Range& rhs) const {
            return this->left <= rhs.left && this->right >= rhs.right;
        }

        inline Range merge(const Range& rhs) const {
            return Range(this->left < rhs.left ? this->left : rhs.left, this->right > rhs.right ? this->right : rhs.right);
        }
    };

    set<Range> ranges;

    inline set<Range>::iterator swim(int bound) {
        return this->swim(bound, this->ranges.begin());
    }

    set<Range>::iterator swim(int bound, set<Range>::iterator start) {
        set<Range>::iterator iter = start;
        while (iter != this->ranges.end() && bound >= iter->left)
            iter++;
        return --iter;
    }
public:
    RangeModule() {
        this->ranges = set<Range>();
        this->ranges.insert(Range(-1, 0));
    }
    
    void addRange(int left, int right) {
        if (this->ranges.size() == 1) {
            this->ranges.insert(Range(left, right));
            printf("add range(%d, %d): ", left, right); this->showRanges();
            return;
        }

        set<Range>::iterator start = this->swim(left), end = this->swim(right, start);

        if (start == end && left > start->right) {
            this->ranges.insert(Range(left, right));
            return;
        }

        Range newRange(left, right);
        if (left > start->right) {
            start++;
        } else {
            newRange.left = start->left;
        }

        if (right <= end->right)
            newRange.right = end->right;

        this->ranges.erase(start, ++end);
        this->ranges.insert(newRange);

        printf("add range(%d, %d): ", left, right); this->showRanges();
    }
    
    bool queryRange(int left, int right) {
        if (this->ranges.size() == 1)
            return false;

        set<Range>::iterator iter = this->swim(left);
        if (left >= iter->left && right <= iter->right)
            return true;
        return false;
    }
    
    void removeRange(int left, int right) {
        if (this->ranges.size() == 1)
            return;

        set<Range>::iterator start = this->swim(left), end = this->swim(right, start);

        if (start == end && left >= start->right) {
            return;
        }

        int sl = 0, er = 0;
        
        if (left >= start->right) {
            start++;
        } else {
            sl = start->left;
        }

        if (right < end->right) {
            er = end->right;
        }

        this->ranges.erase(start, ++end);
        
        if (sl) {
            this->ranges.insert(Range(sl, left));
        }
        if (er) {
            this->ranges.insert(Range(right, er));
        }

        printf("remove range (%d, %d): ", left, right); this->showRanges();
    }

    void showRanges() {
        set<Range>::iterator iter = this->ranges.begin();
        iter++;
        printf("[");
        while (iter != this->ranges.end()) {
            printf("(%d, %d), ", iter->left, iter->right);
            iter++;
        }
        printf("]\n");
    }
};


int main() {
    RangeModule rm;
    rm.addRange(5, 100);
    rm.removeRange(61, 78);
    cout << rm.queryRange(5, 68) << endl;
}
/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
