/*
 Leetcode: 103.�������ľ���β������
 */ 
#include "TreeNode.h"
#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;
/*
   ����������������Ĳ�������Ļ�����֪������Ӧ�ò��ѡ�
   �������Ĳ��������ԭ����Ƕ���ÿһ�������Ľڵ㣬���Ὣ�����ӽڵ�����ӽڵ�push��һ�����С��������ܱ�֤
   ���ȱ������Ľڵ�push�����ӽڵ�����һ��Ҳ�ܹ������ȱ���������

   �����Ҫ���������Ľڵ���ӽڵ����ȱ��������Ļ������ǿ���ѡ����������ջ������ջ����push��һ��Ľڵ㡣
   �� ����ĳһ�����������ڵ㣬��s1�Ѿ�����һ��push�������������ڵ㡣Ȼ����s1�ǿյ�����£�pop����һ������
   �ĸ��ڵ㣬ÿһ��pop���ĸ��ڵ���ӽڵ㶼ѹ��ջs2�С�
   ����һ��ı���˳���Ǵ������ң�����һ�����������Ӧ�����ұߵ��ӽڵ�Ҳ��push��s2����ײ㣬�Ӷ���֤����
   һ��ı���˳�����Ǵ������ҡ�
   ������ֱ�Ӿ���s1���˳���Ǵ������ң�s2���˳���Ǵ�������ע����s2�㽫�ӽڵ�push��s1��ʱ������˳��
   �ȱ����ҽڵ㣬�������ڵ㡣

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
