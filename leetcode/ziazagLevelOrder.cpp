/*
 Leetcode: 103.二叉树的锯齿形层序遍历
 */ 
#include "TreeNode.h"
#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;
/*
   如果有做过二叉树的层序遍历的话，就知道这题应该不难。
   二叉树的层序遍历的原理就是对于每一个遍历的节点，都会将其左子节点和右子节点push进一个队列。这样就能保证
   最先遍历到的节点push进的子节点在下一层也能够被最先被遍历到。

   那如果要最后遍历到的节点的子节点最先被遍历到的话，我们可以选择设立两个栈，两个栈交互push入一层的节点。
   如 ：若某一层有两个父节点，则s1已经在上一层push到了这两个父节点。然后在s1非空的情况下，pop出这一层所有
   的父节点，每一个pop出的父节点的子节点都压入栈s2中。
   若上一层的遍历顺序是从左往右，则这一层从右往左，相应的最右边的子节点也会push到s2的最底层，从而保证了下
   一层的遍历顺序又是从左往右。
   在这里直接就是s1层的顺序都是从左往右，s2层的顺序都是从右往左。注意在s2层将子节点push进s1中时，遍历顺序
   先遍历右节点，后遍历左节点。

  */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        stack<TreeNode*> s1, s2;
        vector<vector<int>> res;
        if (root == NULL) {
            return res;
        }
        s1.push(root);
        TreeNode* tmp;
        int count = 0;
        while (!s1.empty()) {
            //printf("loop\n");
            //level++;
            res.push_back(vector<int>(s1.size()));
            count = 0;
            while (!s1.empty()) {
                tmp = s1.top();
                s1.pop();
                res[res.size() - 1][count++] = tmp->val;
                if (tmp->left != NULL) {
                    s2.push(tmp->left);
                }
                if (tmp->right != NULL) {
                    s2.push(tmp->right);
                }
            } 
            if (s2.empty()) {
                break;
            }
            //level++;
            res.push_back(vector<int>(s2.size()));
            count = 0;
            while (!s2.empty()) {
                tmp = s2.top();
                s2.pop();
                res[res.size()-1][count++] = tmp->val;
                if (tmp->right != NULL) {
                    s1.push(tmp->right);
                }
                if (tmp->left != NULL) {
                    s1.push(tmp->left);
                }
            }
        }
        return res;
    }
};
