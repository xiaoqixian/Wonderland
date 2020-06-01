/*
 Leetcode: 105.��ǰ�����������ؽ������� 
 */
#include "TreeNode.h"
/*
   ����ǰ��������������������ṹ����ǰ������ĵ�һ�����ǵ�ǰ���ڵ��ֵ����������е���ǰ�������һ��ֵ��
   �������������������Ľ�����ұ�����������������Ľ����

   �������ǿ��Թ���һ������build(int i, int j, int startIndex),����startIndex��ʾ�ӽڵ���ǰ������е���
   ����i��j�����������������������нڵ���������������еķ�Χ��

   ��һ�εݹ��У����ǿ����ȸ��ݵ�ǰ�ĸ��ڵ���ǰ������������ҵ�����������е�������������ߵķ�Χ����������
   �����нڵ㣬�ұߵķ�Χ���������������нڵ㡣���ǿ����ٽ��еݹ顣

   �ݹ�ĳ��ڣ������������ֻ��һ���ڵ�ʱ������i=j�������������ΪNULLʱ������i > j��
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
