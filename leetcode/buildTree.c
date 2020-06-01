/*
 Leetcode: 105.从前序和中序遍历重建二叉树 
 */
#include "TreeNode.h"
/*
   利用前序遍历和中序遍历的特殊结构，即前序遍历的第一个总是当前父节点的值，中序遍历中等于前序遍历第一个值的
   左边是左子树中序遍历的结果，右边是右子树中序遍历的结果。

   于是我们可以构造一个函数build(int i, int j, int startIndex),参数startIndex表示子节点在前序遍历中的索
   引。i和j则是左子树或右子树的所有节点在中序遍历数组中的范围。

   在一次递归中，我们可以先根据当前的父节点在前序遍历的索引找到在中序遍历中的索引，索引左边的范围就是左子树
   的所有节点，右边的范围就是右子树的所有节点。于是可以再进行递归。

   递归的出口：当左或右子树只有一个节点时，则有i=j。当左或右子树为NULL时，则有i > j。
  */

int* pre, *ino;
struct TreeNode* build(int, int, int);

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    pre = preorder;
    ino = inorder;
    return build(0, preorderSize-1, 0);
}

struct TreeNode* build(int i, int j, int startIndex) {
    if (j < i) {
        return NULL;
    }
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = pre[startIndex];
    node->left = NULL;
    node->right = NULL;
    if (j == i) {
        return node;
    }
    else {
        int mid;
        for (mid = i; mid < j; mid++) {
            if (ino[mid] == pre[startIndex]) {
                break;
            }
        }
        node->left = build(i, mid - 1, startIndex+1);
        node->right = build(mid + 1, j, startIndex+mid-i+1);
        return node;
    }
}
