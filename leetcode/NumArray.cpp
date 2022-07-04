/**********************************************
  > File Name		: NumArray.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 21:03:59 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <map>
using namespace std;

class NumArray {
public:
    vector<int> tree;
    vector<int> &nums;

    int lowBit(int x) {
        return x & -x;
    }

    void add(int index, int val) {
        while (index < tree.size()) {
            tree[index] += val;
            index += lowBit(index);
        }
    }

    int prefixSum(int index) {
        int sum = 0;
        while (index > 0) {
            printf("index = %d\n", index);
            sum += tree[index];
            index -= lowBit(index);
        }
        return sum;
    }

public:
    NumArray(vector<int>&& nums) : tree(nums.size() + 1), nums(nums) {
        for (int i = 0; i < nums.size(); i++) {
            add(i + 1, nums[i]);
        }
    }

    void update(int index, int val) {
        add(index + 1, val - nums[index]);
        nums[index] = val;
    }

    int sumRange(int left, int right) {
        return prefixSum(right + 1) - prefixSum(left);
    }
};

int main() {
    NumArray na({0, 9, 5, 7, 3});
    printf("%d\n", na.prefixSum(4));
}

class NumArray3 {
private:
    int getSize(int size) {
        int res = 0;
        while (size) {
            res++;
            size >>= 1;
        }
        return (1<<res) - 1;
    }

    void buildArray(int base, int len) {
        int upper_size = (len >> 1) + (len % 2);
        int pos = base - upper_size;
        const int anchor = base;
        while (len) {
            this->treeArray[pos] += this->treeArray[base];
            this->bounds[pos] = base < this->offset ? this->bounds[base] : Bound(base - anchor, base - anchor);
            base++;

            if (--len) {
                this->treeArray[pos] += this->treeArray[base];
                this->bounds[pos].right_bound = base < this->offset ? this->bounds[base].right_bound : base - anchor;

                base++;
                len--;
            }
            pos++;
        }
        if (upper_size > 1)
            buildArray(anchor - upper_size, upper_size);
    }

    int _sumRange(const int left, const int right, int index) const {
        if (left == right)
            return this->treeArray[this->offset + left];

        const auto& b = this->bounds[index];
        if (left == b.left_bound && right == b.right_bound)
            return this->treeArray[index];

        //now, we can be sure that index is not a leaf node.
        const int left_part = (index << 1) + 1, right_part = left_part + 1;
        const auto& lb = this->bounds[left_part];
        const int mid = lb.right_bound;
        
        if (right <= mid)
            return this->_sumRange(left, right, left_part);
        else if (left > mid)
            return this->_sumRange(left, right, right_part);
        else
            return this->_sumRange(left, mid, left_part) + this->_sumRange(mid+1, right, right_part);
    }

    struct Bound {
        uint16_t left_bound;
        uint16_t right_bound;

        Bound(): left_bound(0), right_bound(0) {}
        Bound(int lb, int rb): left_bound(lb), right_bound(rb) {}
    } __attribute__((packed));

    vector<int> treeArray;
    vector<Bound> bounds;
    int offset;
public:
    NumArray3(const vector<int>& nums) {
        const int size = getSize(nums.size());

        this->offset = size; 
        this->treeArray = vector<int>(this->offset, 0);
        this->bounds = vector<Bound>(this->offset, Bound());
        const auto pos = this->treeArray.end();
        this->treeArray.insert(pos, nums.begin(), nums.end());

        this->buildArray(this->offset, nums.size());
    }

    void update(const int index, const int val) {
        int cursor = 0;
        const int size = this->treeArray.size();
        const int diff = val - this->treeArray[this->offset + index];
        
        while (cursor < size) {
            this->treeArray[cursor] += diff;
            
            const int left_part = (cursor << 1) + 1, mid = left_part < this->offset ? this->bounds[left_part].right_bound : this->bounds[cursor].left_bound;
            if (index <= mid)
                cursor = left_part;
            else
                cursor = left_part + 1;
        }
    }

    const int sumRange(const int left, const int right) const {
        return this->_sumRange(left, right, 0);
    }
};

class NumArray2 {
private:
    struct Node {
        int left_bound, right_bound;
        int sum;
        Node* left, *right;
        Node(int lb, int rb, int sum): left_bound(lb), right_bound(rb), sum(sum), left(nullptr), right(nullptr) {}
    };

    Node* buildTree(const vector<int>& nums, int lb, int rb) {
        if (lb == rb) {
            return new Node(lb, rb, nums[lb]);
        }

        if (lb == rb - 1) {
            return new Node(lb, rb, nums[lb] + nums[rb]);
        }

        const int mid = (lb + rb) >> 1;
        Node* left_part = buildTree(nums, lb, mid), *right_part = buildTree(nums, mid+1, rb);

        Node* res = new Node(lb, rb, left_part->sum + right_part->sum);
        res->left = left_part; res->right = right_part;
        return res;
    }

    Node* root;
    vector<int> nums;

    int sumRange_(const Node* node, int left, int right) {
        if (left == right)
            return this->nums[left];

        if (left == node->left_bound && right == node->right_bound)
            return node->sum;

        const int mid = (node->left_bound + node->right_bound) >> 1;

        if (right <= mid)
            return this->sumRange_(node->left, left, right);
        else if (left > mid)
            return this->sumRange_(node->right, left, right);
        else
            return this->sumRange_(node->left, left, mid) + this->sumRange_(node->right, mid, right);
    }
public:
    NumArray2(const vector<int>& nums) {
        this->root = buildTree(nums, 0, nums.size()-1);
        this->nums = nums;
    }

    void update(int index, int val) {
        const int diff = val - this->nums[index];
        this->nums[index] = val;

        Node* cursor = this->root;

        while (cursor != nullptr) {
            cursor->sum += diff;
            int mid = (cursor->left_bound + cursor->right_bound) >> 1;
            if (index <= mid)
                cursor = cursor->left;
            else
                cursor = cursor->right;
        }
    }

    int sumRange(int left, int right) {
        return this->sumRange_(this->root, left, right);
    }
};

class NumArray1 {
private:
    map<int, int> updates;
    vector<int> nums, rangeSum;
public:
    NumArray1(vector<int>& nums) {
        this->nums = nums;
        this->rangeSum = vector<int>(nums.size(), 0);
        this->rangeSum[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            this->rangeSum[i] = this->rangeSum[i-1] + nums[i];
        }
    }

    void update(int index, int val) {
        int diff = val - nums[index];
        nums[index] = val;

        auto it = this->updates.find(index);
        if (it == this->updates.end()) {
            this->updates.insert({index, diff});
        } else {
            this->updates[index] += diff;
        }
    }

    int sumRange(int left, int right) {
        auto lower = this->updates.lower_bound(left);
        int diff = this->rangeSum[right] - this->rangeSum[left];
        if (lower == this->updates.end()) {
            return diff;
        }

        auto upper = this->updates.upper_bound(right);
        while (lower != upper) {
            diff += lower->second;
            lower++;
        }
        return diff;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
