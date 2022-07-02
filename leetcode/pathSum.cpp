/*
 Leetcode: 437.路徑总和III 
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
 * 本题主要是两步，对于一个节点，首先是找出所有以本节点为起始节点的路径数量，然后递归调用查询本节点的左节点
 * 和右节点。
 */

#include "TreeNode.h"

class Solution {
public:
    /*
     在nodeSum函数可以找出对于某个父节点为起始节点的路径数量的情况下，pathSum函数只需要负责遍历所有的节点就可以
    找出所有的路径数量。遍历树中的节点采用递归的方式。
    */
    int res = 0; //由于需要递归，所以将路径数量设立在函数之外。
    int pathSum(TreeNode* root, int sum) {
        if (root == NULL) {
            return 0;
        }
        res += nodeSum(root, sum);
        pathSum(root->left, sum);
        pathSum(root->right, sum);
        return res;
    }

    /*
     nodeSum负责找出所有以node节点为起始节点的和等于sum的路径数量。
     基本思想为：递归查询左子节点和右子节点，递归时的第二个参数为sum - node->val
     */
    int nodeSum(TreeNode* node, int sum) {
        if (node == NULL) {
            return 0;
        }
        int flag = 0; //flag用于标识当前路径是否已经满足，如果满足，则结果需要加1.
        if (node->val == sum) {
            flag = 1;
        }
        return flag + nodeSum(node->left, sum-node->val) + nodeSum(node->right, sum-node->val);
    }
};
