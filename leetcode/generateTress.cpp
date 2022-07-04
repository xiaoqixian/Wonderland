/**********************************************
  > File Name		: generateTress.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 14:23:38 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <iostream>
#include <unordered_map>
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
private:
    TreeNode* copyTree(const TreeNode* t) {
        if (t == nullptr)
            return nullptr;
        TreeNode* root = new TreeNode(*t);
        root->left = copyTree(t->left);
        root->right = copyTree(t->right);
        return root;
    }

    TreeNode* findRightMost(TreeNode* root) {
        if (root == nullptr)
            return nullptr;
        while (root->right != nullptr)
            root = root->right;
        return root;
    }

    unordered_map<int, vector<TreeNode*>> m;

public:
    vector<TreeNode*> generateTrees(int n) {
        auto iter = this->m.find(n);
        if (iter != this->m.end()) {
            return iter->second;
        }

        if (n == 1) {
            vector<TreeNode*> res = {new TreeNode(1)};
            this->m.insert({n, res});
            return res;
        }

        vector<TreeNode*> res;
        auto lastRes = this->generateTrees(n-1);
        
        for (auto t: lastRes) {
            this->insertNode(res, t, n);
        }

        this->m.insert({n, res});
        return res;
    }

    void insertNode(vector<TreeNode*>& trees, TreeNode* t, int n) {
        TreeNode* upper = nullptr, *lower = t, *root = t;

        while (lower != nullptr || upper != nullptr) {
            TreeNode* newNode = new TreeNode(n);
            if (upper == nullptr) {
                newNode->left = copyTree(t);
                trees.push_back(newNode);
                
                upper = lower;
                lower = lower->right;
                continue;
            }

            assert(upper->right == lower);
            upper->right = nullptr;//temporary
            TreeNode* newRoot = copyTree(root);
            upper->right = lower;

            TreeNode* newUpper = findRightMost(newRoot);
            newUpper->right = newNode;
            newNode->left = copyTree(lower);

            trees.push_back(newRoot);
            upper = lower;
            lower = lower == nullptr ? nullptr : lower->right;
        }
    }
};

int main() {}
