/**********************************************
  > File Name		: lowestCommonAncestor.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Jul  4 23:23:54 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <deque>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    void getPath(deque<TreeNode*>& path, TreeNode* target, TreeNode* root, bool& found) {
        path.push_back(root);

        if (root == target) {
            found = true;
            return;
        }

        if (root->left != nullptr)
            getPath(path, target, root->left, found);
        if (found)
            return;

        if (root->right != nullptr)
            getPath(path, target, root->right, found);
        if (found)
            return;

        path.pop_back();
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        deque<TreeNode*> p_path, q_path;
        bool p_found = false, q_found = false;
        getPath(p_path, p, root, p_found);
        assert(p_found);
        getPath(q_path, q, root, q_found);
        assert(q_found);

        TreeNode* p_node = nullptr, *q_node = nullptr;
        while (!p_path.empty() && !q_path.empty()) {
            if (p_path.front() != q_path.front()) {
                return p_node;
            }

            p_node = p_path.front();
            q_node = q_path.front();
            p_path.pop_front();
            q_path.pop_front();
        }

        if (p_path.empty())
            return p_node;
        else if (q_path.empty())
            return q_node;
        else return nullptr;
    }
};
