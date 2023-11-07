// Date: Sun Nov 05 12:08:45 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector> 
#include <map>

class SegmentTree {
    std::vector<long long> tree;

    long long findRangeMax(const size_t ub, const size_t l, const size_t r) const {
        const int mid = l + ((r - l) >> 1);
        if (mid == ub) {
            return this->tree[mid];
        } else if (mid < ub) {
            return std::max(this->tree[mid], findRangeMax(ub, mid+1, r));
        } else {
            return findRangeMax(ub, l, mid-1);
        }
    }
public:
    SegmentTree(const int n) {
        this->tree = std::vector<long long>(n, LLONG_MIN);
    }

    void assign(size_t index, long long val) {
        size_t l = 0, r = this->tree.size(), mid = l + ((r - l) >> 1);
        while (mid != index) {
            if (index < mid) {
                this->tree[mid] = std::max(this->tree[mid], val);
                r = mid-1;
            } else l = mid+1;
            mid = l + ((r - l) >> 1);
        }
        this->tree[mid] = std::max(this->tree[mid], val);
    }

    long long operator[](size_t index) const {
        return this->findRangeMax(index, 0, this->tree.size());
    }

    long long max() const {
        return *std::max_element(this->tree.cbegin(), this->tree.cend());
    }
};

class Solution {
public:
    long long maxBalancedSubsequenceSum(std::vector<int> const& nums) {
        const int n = nums.size();

        std::map<int, int> pos_dict;
        for (int i = 0; i < n; i++) {
            pos_dict.insert({nums[i] - i, i});
        }
        int pos = 0;
        for (auto it = pos_dict.begin(); it != pos_dict.end(); it++) {
            it->second = pos++;
        }

        SegmentTree st(pos_dict.size());
        for (size_t i = 0; i < n; i++) {
            const int key = nums[i] - i;
            const int pos = pos_dict[key];
            const long long pos_sum = st[pos];
            st.assign(pos, pos_sum > 0 ? pos_sum + nums[i] : (long long)nums[i]);
        }

        return st.max();
    }
};
