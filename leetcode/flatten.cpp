/**********************************************
  > File Name		: flatten.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Dec 28 15:28:06 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* visit(TreeNode* node) {
        TreeNode* last = node;
        TreeNode* left = node->left, *right = node->right;
        if (left != nullptr) {
            last->left = nullptr;
            last->right = left;
            last = visit(left);
        }
        if (right != nullptr) {
            last->left = nullptr;
            last->right = right;
            last = visit(right);
        }
        return last;
    }
    void flatten(TreeNode* root) {
        visit(root);
    }
};
