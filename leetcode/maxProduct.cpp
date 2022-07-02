/*
 1339.���Ѷ����������˻�
 */
 
#include <stdio.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	//struct TreeNode(int x): val(x), left(NULL), right(NULL) {}
}; 

//��֪����֮�����ʱ��ֻ�������������ʱ���ǵĳ˻����
//���Ա�������ҵ����Խ����ֳ������;�������������Ľ�㡣 
class Solution {
	public:
		int min_min, min_max, sum;
		int maxProduct(TreeNode* root) {
			sum = sumAll(root);
			min_min = 0, min_max = sum;
			dfs(root);
			int diff = 
			return 0;
		}
		
		/*������������������ڵ㣬����ÿ�εݹ��е�root��㶼������Ͳ����������õĺ�С��sum��һ�룬��ֹͣ��ͣ���Ϊ
		 �������ӽڵ����Ϳ϶����������С�� 
		 */ 
		void dfs(TreeNode* root) {
			int tmp_sum = sumAll(root);
			tmp_sum <<= 1;
			if (tmp_sum == sum) {
				min_min = 0;
				min_max = 0;
				return ;
			}
			else if (tmp_sum > sum) {
				if (tmp_sum - sum < min_max) {
					min_max = tmp_sum - sum;
				}
				if (root->left != NULL) {
					dfs(root->left);
				}
				if (root->right != NULL) {
					dfs(root->right);
				}
			}
			else {
				if (tmp_sum - sum > min_min) {
					min_min = tmp_sum - sum;
				}
				return ;
			}
		}
		
		int sumAll(TreeNode* root) {
			if (root == NULL) {
				return 0;
			}
			return (root->val + sumAll(root->left) + sumAll(root->right));
		}
};

int main() {
	int s = -7;
	printf("%f\n", abs(s));
	return 0;
}
