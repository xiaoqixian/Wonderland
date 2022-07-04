/**********************************************
  > File Name		: isValidBST.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 17:12:25 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <utility>

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
    bool isValidBST(TreeNode* root) {
        bool res = true;
        findMost(root, res);
        return res;
    }

    std::pair<int, int> findMost(TreeNode* root, bool& res) {
        int minimal = root->val, maximal = root->val;
        
        if (root->left != nullptr) {
            auto p = findMost(root->left, res);
            if (!res) {
                return {0, 0};
            }
            if (p.second > root->val) {
                res = false;
                return {0, 0};
            } else {
                minimal = p.first;
            }
        }

        if (root->right != nullptr) {
            auto p = findMost(root->right, res);
            if (!res) {
                return {0, 0};
            }
            if (p.first < root->val) {
                res = false;
                return {0, 0};
            } else {
                maximal = p.second;
            }
        }

        return {minimal, maximal};
    }
};

int main() {}
