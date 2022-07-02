/**********************************************
  > File Name		: BSTIterator.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 02 Jun 2022 09:49:22 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BSTIterator {
private:
    TreeNode* root;
    std::queue<int> q;
public:
    BSTIterator(TreeNode* root) {
        this->root = root;
        this->search(root);
    }

    void search(TreeNode* root) {
        if (root->left != nullptr) {
            this->search(root->left);
        }

        this->q.push(root->val);

        if (root->right != nullptr) {
            this->search(root->right);
        }
    }
    
    int next() {
        int res = this->q.front();
        this->q.pop();
        return res;
    }
    
    bool hasNext() {
        return !this->q.empty();
    }
};

#include <stack>

class BSTIterator2 {
private:
    std::stack<TreeNode*> path;
public:
    BSTIterator2(TreeNode* root) {
        this->path.push(root);
        while (path.top()->left != nullptr) {
            path.push(path.top()->left);
        }
    }

    int next() {
        TreeNode* top = this->path.top();
        this->path.pop();

        if (top->right != nullptr) {
            TreeNode* temp = top->right;
            this->path.push(temp);
            while (temp->left != nullptr) {
                temp = temp->left;
                this->path.push(temp);
            }
        }

        return top->val;
    }

    bool hasNext() {
        return !this->path.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
