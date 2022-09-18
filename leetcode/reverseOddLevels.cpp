/**********************************************
  > File Name		: reverseOddLevels.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep 18 10:43:22 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <queue>
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
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        queue<int> postorder_nums;
        queue<TreeNode*> preorder, postorder;

        postorder.push(root);
        while (!postorder.empty()) {
            TreeNode* cursor = postorder.front();
            postorder.pop();

            if (cursor->right != nullptr) {
                postorder.push(cursor->right);
                postorder.push(cursor->left);
            }

            postorder_nums.push(cursor->val);
        }

        int level = 0, level_count = 0, level_expect = 1;
        preorder.push(root);
        while (!preorder.empty()) {
            TreeNode* cursor = preorder.front();
            preorder.pop();
            level_count++;

            if (level % 2) {
                cursor->val = postorder_nums.front();
            }

            postorder_nums.pop();

            if (cursor->right != nullptr) {
                preorder.push(cursor->left);
                preorder.push(cursor->right);
            }

            if (level_count == level_expect) {
                level++;
                level_expect <<= 1;
                level_count = 0;
            }
        }

        return root;
    }
};
