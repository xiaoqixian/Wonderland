/**********************************************
  > File Name		: maxSumBST.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 18 Dec 2021 02:32:03 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//struct LinkedNode {
    //TreeNode* node;
    //TreeNode* prev;
    //TreeNode* next;
    
    //LinkedNode(TreeNode* node) : node(node), prev(nullptr), next(nullptr) {}
//};

#define INVALID_NUM 40002
#define MAX 40001
#define MIN -40001
class Solution {
private:
    int res;
public:
     int maxSumBST(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        this->res = 0;
        int curr_min = MAX, curr_max = MIN;
        int left_res, right_res;
        bool left_flag = false, right_flag = false;
        if (root->left != nullptr) {
            left_res = this->dfs(root->left, curr_min, curr_max);
            if (left_res == INVALID_NUM || curr_max >= root->val) {
                left_flag = true;
            }
        }

        if (root->right != nullptr) {
            right_res = this->dfs(root->right, curr_min, curr_max);
            if (right_res == INVALID_NUM || curr_min <= root->val) {
                right_flag = true;
            }
        }

        if (!left_flag && !right_flag) {
            int sum = root->val + left_res + right_res;
            return sum > this->res ? sum : this->res;
        }
        return this->res;
    }

    int dfs(TreeNode* node, int& min, int& max) {
        bool left_flag = false, right_flag = false, leaf_node = false;
        int left_res = 0, right_res = 0;
        int curr_min = MAX, curr_max = MIN;

        if (node->left == nullptr && node->right == nullptr) {
            leaf_node = true;
        }

        if (node->left != nullptr) {
            left_res = this->dfs(node->left, curr_min, curr_max);
            if (left_res == INVALID_NUM || curr_max >= node->val) {
                left_flag = true; //left child is not a BST
            } else {
                min = curr_min;
            }
            curr_min = MAX; curr_max = MIN;
        } else {
            min = node->val;
        }

        if (node->right != nullptr) {
            right_res = this->dfs(node->right, curr_min, curr_max);
            if (right_res == INVALID_NUM || curr_min <= node->val) {
                right_flag = true;
            } else {
                max = curr_max;
            }
        } else {
            max = node->val;
        }

        if (left_flag || right_flag) {
            return INVALID_NUM;
        }

        int sum = node->val + left_res + right_res;
        if (sum > this->res) {
            this->res = sum;
        }
        return sum;
    }
};

#define null 0xBEEF
TreeNode* generate(vector<int>& vals) {
    int i = 0, s = vals.size();
    if (vals[0] == null) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(vals[i++]);
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* node = nullptr, *child = nullptr;
    
    while (!q.empty()) {
        node = q.front();
        q.pop();
        
        if (node == nullptr) {
            i += 2;
            continue;
        }

        printf("generating %d\n", node->val);

        if (vals[i] == null) {
            child = nullptr;
        } else {
            child = new TreeNode(vals[i]);
        }
        
        node->left = child;
        q.push(child);
        i++;
        if (i == s)
            break;

        if (vals[i] == null) {
            child = nullptr;
        } else {
            child = new TreeNode(vals[i]);
        }
        
        node->right = child;
        q.push(child);
        i++;
        if (i == s)
            break;
    }

    return root;
}

int main() {
    //vector<int> vals = {1,4,3,2,4,2,5,null,null,null,null,null,null,4,6};
    //vector<int> vals = {4,3,null,1,2};
    vector<int> vals = {8,9,8,null,9,null,1,null,null,-3,5,null,-2,null,6};
    TreeNode* root = generate(vals);
    Solution s;
    printf("%d\n", s.maxSumBST(root));
    return 0;
}
