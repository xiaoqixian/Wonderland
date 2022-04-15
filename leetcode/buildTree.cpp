/**********************************************
  > File Name		: buildTree.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 15 Apr 2022 04:33:25 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return nullptr;

        return _buildTree(preorder, inorder, make_pair(0, preorder.size()-1), 
                make_pair(0, inorder.size()-1));
    }

private:
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, 
            pair<int, int> preBound, pair<int, int> inBound) {
        TreeNode* root = new TreeNode(preorder[preBound.first]);

        if (preBound.first == preBound.second)
            return root;

        int inRootIndex = inBound.first, rootVal = preorder[preBound.first];
        while (inorder[inRootIndex] != rootVal)
            inRootIndex++;

        int leftTreeLength = 0;
        
        if (inRootIndex > inBound.first) {
            leftTreeLength = inRootIndex - inBound.first;
            root->left = _buildTree(preorder, inorder, 
                    make_pair(preBound.first + 1, preBound.first + leftTreeLength),
                    make_pair(inBound.first, inRootIndex - 1));
        }

        if (inRootIndex > inBound.second) {
            root->right = _buildTree(preorder, inorder, 
                    make_pair(preBound.first + leftTreeLength + 1, preBound.second),
                    (make_pair(inRootIndex + 1, inBound.second)));
        }

        return root;
    }
};

class Solution2 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};

