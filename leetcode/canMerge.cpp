/**********************************************
  > File Name		: canMerge.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 14 Feb 2022 09:48:26 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/


#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <limits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    typedef TreeNode* NodePtr;
    pair<NodePtr, size_t> merge_tree(const vector<NodePtr>& trees) {
        auto cmp1 = [](const auto& t, const auto& u) { return t.first < u.first; };
        auto cmp2 = [](const auto& t, int u) { return t.first < u; };

        auto size = trees.size(), nroot = size;
        // 理论上开足优化的话这里用vector应该是一样的
        // 但是不知道为什么改成vector以后性能就只排60%了
        unique_ptr<pair<int, int>[]> work_space1 (new pair<int, int>[size]);
        unique_ptr<int[]>            work_space2 (new int[size]);
        auto roots_begin = work_space1.get(), roots_end = roots_begin + size;
        //marker 用于表示节点之间的指向关系
        auto marker = work_space2.get();

        // 构造有序表供查找
        for(size_t i = 0; i != size; ++i) {
            roots_begin[i].first = trees[i]->val;
            roots_begin[i].second = i;
        }
        sort(roots_begin, roots_end, cmp1);

        // 合并树
        for(size_t i = 0; i != size; ++i) {
            marker[i] = i;
        }
        for(size_t i = 0; i != size; ++i) {
            auto t = trees[i];

            // 找当前 trees[i] 的根
            int x = i, p = marker[x], gp = marker[p];
            while (gp != p) {
                marker[x] = gp;  // 压缩路径
                x = gp;
                p = marker[x];
                gp = marker[p];
            }
            x = p; //x 现在在root出

            if(t->left != nullptr) {
                auto left_val = t->left->val;
                auto it = lower_bound(roots_begin, roots_end, left_val, cmp2);
                if(it != roots_end && it->first == left_val) {
                    auto y = it->second;
                    if(marker[y] == y && x != y) { // 合并进来的子树是根，且不是当前子树的根
                        marker[y] = x;
                        -- nroot;
                        t->left = trees[y];
                    }
                }
            }

            if(t->right != nullptr) {
                auto right_val = t->right->val;
                auto it = lower_bound(roots_begin, roots_end, right_val, cmp2);
                if(it != roots_end && it->first == right_val) {
                    auto y = it->second;
                    if(marker[y] == y && x != y) { // 合并进来的子树是根，且不是当前子树的根
                        marker[y] = x;
                        -- nroot;
                        t->right = trees[y];
                    }
                }
            }
        }
        TreeNode* root = nullptr;
        for(size_t i = 0; i != size; ++i) {
            if(marker[i] == i) {
                root = trees[i];
                break;
            }
        }
        return {root, nroot};
    }

    // 非递归中序遍历, 检查合并后是否是BST
    bool check_bst(NodePtr root, size_t size) {
        unique_ptr<NodePtr[]> work_space (new NodePtr[size + 1]); 
        auto top = work_space.get();
        auto last = numeric_limits<int>::min();

        // 虚拟节点
        TreeNode tmp, *dummy = &tmp;
        dummy->right = dummy;
        dummy->val = numeric_limits<int>::max();
        *(top++) = dummy;

        for (auto c = root; c != dummy; ) {
            for(auto l = c->left; l != nullptr; l = c->left) {
                *(top++) = c;
                c = l;
            }
            if(last >= c->val) { // 检查序关系
                return false;
            }
            last = c->val;

            TreeNode* right;
            for(right = c->right; right == nullptr; right = c->right) {
                c = *(--top);
                if(last >= c->val) { // 检查序关系
                    return false;
                }
                last = c->val;
            }
            c = right;
        }
        return true;
    }

public:
    TreeNode* canMerge(const vector<TreeNode*>& trees) {
        auto res = merge_tree(trees);
        // 是否有且仅有一个根，否则不能合并
        return (res.second == 1 && check_bst(res.first, trees.size())) ? res.first : nullptr;
    }
};

class Solution1 {
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, TreeNode*> left, right;
        unordered_map<int, TreeNode*>::iterator iter;
        for (TreeNode* node: trees) {
            if (this->is_circle(left, right, node))
                return nullptr;
            if (node->left != nullptr) {
                if (this->is_child(left, right, node->left->val))
                    return nullptr;
                left.insert({node->left->val, node});
                //root.insert({node->left->val, node->val});
            }
            if (node->right != nullptr) {
                if (this->is_child(left, right, node->right->val))
                    return nullptr;
                right.insert({node->right->val, node});
                //root.insert({node->right->val, node->val});
            }
        }

        TreeNode* root = nullptr;
        for (TreeNode* node: trees) {
            printf("set %d\n", node->val);
            iter = left.find(node->val);
            if (iter != left.end()) {
                printf("%d become %d left child\n", node->val, iter->second->val);
                iter->second->left = node;
            } else {
                iter = right.find(node->val);
                if (iter != right.end()) {
                    printf("%d become %d right child\n", node->val, iter->second->val);
                    iter->second->right = node;
                } else {
                    if (root == nullptr) {
                        root = node;
                    } else {
                        return nullptr;
                    }
                }
            }
        }

        if (!this->check_bst(root, trees.size()))
            return nullptr;
        return root;
    }

    bool is_child(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, int val) {
        unordered_map<int, TreeNode*>::iterator iter = left.find(val);
        if (iter != left.end())
            return true;
        else {
            iter = right.find(val);
            if (iter != right.end())
                return true;
            else return false;
        }
    }

    bool is_circle(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, TreeNode* node) {
        unordered_map<int, TreeNode*>::iterator iter = left.find(node->val);

        if (node->left != nullptr && this->search_tree(left, right, node->left->val, node->val))
            return true;
        else if (node->right != nullptr && this->search_tree(left, right, node->right->val, node->val))
            return true;
        else return false;
    }

    bool search_tree(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, int val, int start) {
        unordered_map<int, TreeNode*>::iterator iter = left.find(start);
        int temp = start;
        do {
            while (iter != left.end()) {
                temp = iter->second->val;
                if (temp == val)
                    return true;
                iter = left.find(temp);
            }

            iter = right.find(temp);
            while (iter != right.end()) {
                temp = iter->second->val;
                if (temp == val)
                    return true;
                iter = right.find(temp);
            }
        } while ((iter = left.find(temp)) != left.end());
        return false;
    }
    bool check_bst(TreeNode* root, size_t size) {
        unique_ptr<TreeNode*[]> work_space (new TreeNode*[size + 1]); 
        auto top = work_space.get();
        auto last = numeric_limits<int>::min();

        // 虚拟节点
        TreeNode tmp, *dummy = &tmp;
        dummy->right = dummy;
        dummy->val = numeric_limits<int>::max();
        *(top++) = dummy;

        for (auto c = root; c != dummy; ) {
            for(auto l = c->left; l != nullptr; l = c->left) {
                *(top++) = c;
                c = l;
            }
            if(last >= c->val) { // 检查序关系
                return false;
            }
            last = c->val;

            TreeNode* right;
            for(right = c->right; right == nullptr; right = c->right) {
                c = *(--top);
                if(last >= c->val) { // 检查序关系
                    return false;
                }
                last = c->val;
            }
            c = right;
        }
        return true;
    }

    bool check(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, TreeNode* node) {
        if (node->left == nullptr && node->right == nullptr)
            return true;
        int temp = node->val;
        unordered_map<int, TreeNode*>::iterator iter = left.find(temp);
        int lower = 0, upper = 50000;

        if (iter == left.end()) {
            iter = right.find(temp);

            if (iter != right.end()) {
                lower = max(lower, iter->second->val);
                while (iter != right.end()) {
                    temp = iter->second->val;
                    iter = right.find(temp);
                }
            }

            iter = left.find(temp);
            if (iter != left.end())
                upper = min(upper, iter->second->val);
        } else
            upper = min(upper, iter->second->val);

        if (node->left != nullptr && node->left->val <= lower)
            return false;
        if (node->right != nullptr && node->right->val >= upper)
            return false;
        return true;
    }

/*    int trace_up_max(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, int val) {*/
        /*unordered_map<int, TreeNode*>::iterator iter;*/
        /*int res = val;*/
        /*printf("trace up max for %d = ", val);*/
        
        /*iter = right.find(val);*/
        /*do {*/
            /*while (iter != right.end()) {*/
                /*val = iter->second->val;*/
                /*iter = right.find(val);*/
            /*}*/

            /*iter = left.find(val);*/
            /*while (iter != left.end()) {*/
                /*val = iter->second->val;*/
                /*res = val;*/
                /*iter = left.find(val);*/
            /*}*/
        /*} while ((iter = right.find(val)) != right.end())*/
        /*printf("%d\n", res);*/
        /*return res;*/
    /*}*/

    /*int trace_up_min(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, int val) {*/
        /*unordered_map<int, TreeNode*>::iterator iter;*/
        /*int res = val;*/
        /*printf("trace up max for %d = ", val);*/
        
        /*iter = left.find(val);*/
        /*do {*/
            /*while (iter != left.end()) {*/
                /*val = iter->second->val;*/
                /*iter = left.find(val);*/
            /*}*/

            /*iter = right.find(val);*/
            /*while (iter != right.end()) {*/
                /*val = iter->second->val;*/
                /*res = val;*/
                /*iter = right.find(val);*/
            /*}*/
        /*} while ((iter = left.find(val)) != left.end())*/
        /*printf("%d\n", res);*/
        /*return res;*/
    /*}*/

    /*int trace_up_max1(unordered_map<int, TreeNode*>& left, unordered_map<int, TreeNode*>& right, int val) {*/
        /*unordered_map<int, TreeNode*>::iterator iter;*/
        /*int res = 50000;*/
        /*printf("trace up max for %d = ", val);*/
        
        /*iter = right.find(val);*/
        /*while (iter != right.end()) {*/
            /*val = iter->second->val;*/
            /*iter = right.find(val);*/
        /*}*/

        /*iter = left.find(val);*/
        /*while (iter != left.end()) {*/
            /*val = iter->second->val;*/
            /*res = val;*/
            /*iter = left.find(val);*/
        /*}*/
        /*printf("%d\n", res);*/
        /*return res;*/
    /*}*/

    /*inline int trace_up_min1(unordered_map<int, TreeNode*>& right, unordered_map<int, TreeNode*>& left, int val) {*/
        /*unordered_map<int, TreeNode*>::iterator iter;*/
        /*int res = 0;*/
        /*printf("trace up max for %d = ", val);*/
        
        /*iter = right.find(val);*/
        /*while (iter != right.end()) {*/
            /*val = iter->second->val;*/
            /*iter = right.find(val);*/
        /*}*/

        /*iter = left.find(val);*/
        /*while (iter != left.end()) {*/
            /*val = iter->second->val;*/
            /*res = val;*/
            /*iter = left.find(val);*/
        /*}*/
        /*printf("%d\n", res);*/
        /*return res;*/
    /*}*/

    int trace_down_right(TreeNode* root) {
        int res = root->val;
        while (root->right != nullptr) {
            root = root->right;
            res = root->val;
        }
        return res;
    }

    int trace_down_left(TreeNode* root) {
        int res = root->val;
        while (root->left != nullptr) {
            root = root->left;
            res = root->val;
        }
        return res;
    }

};
