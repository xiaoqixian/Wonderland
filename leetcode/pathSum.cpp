/*
 Leetcode: 437.·���ܺ�III 
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
 * ������Ҫ������������һ���ڵ㣬�������ҳ������Ա��ڵ�Ϊ��ʼ�ڵ��·��������Ȼ��ݹ���ò�ѯ���ڵ����ڵ�
 * ���ҽڵ㡣
 */

#include "TreeNode.h"

class Solution {
public:
    /*
     ��nodeSum���������ҳ�����ĳ�����ڵ�Ϊ��ʼ�ڵ��·������������£�pathSum����ֻ��Ҫ����������еĽڵ�Ϳ���
    �ҳ����е�·���������������еĽڵ���õݹ�ķ�ʽ��
    */
    int res = 0; //������Ҫ�ݹ飬���Խ�·�����������ں���֮�⡣
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
     nodeSum�����ҳ�������node�ڵ�Ϊ��ʼ�ڵ�ĺ͵���sum��·��������
     ����˼��Ϊ���ݹ��ѯ���ӽڵ�����ӽڵ㣬�ݹ�ʱ�ĵڶ�������Ϊsum - node->val
     */
    int nodeSum(TreeNode* node, int sum) {
        if (node == NULL) {
            return 0;
        }
        int flag = 0; //flag���ڱ�ʶ��ǰ·���Ƿ��Ѿ����㣬������㣬������Ҫ��1.
        if (node->val == sum) {
            flag = 1;
        }
        return flag + nodeSum(node->left, sum-node->val) + nodeSum(node->right, sum-node->val);
    }
};
