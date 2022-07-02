/*
 由于在做Leetcode时二叉树的题目往往具有相同的结构体，所以特意写一个头文件定义，省的每一次都写一遍 
 */ 
 
#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

#endif
