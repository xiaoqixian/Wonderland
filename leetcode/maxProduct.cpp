/*
 1339.分裂二叉树的最大乘积
 */
 
#include <stdio.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	//struct TreeNode(int x): val(x), left(NULL), right(NULL) {}
}; 

//易知两数之和相等时，只有在两个数相等时它们的乘积最大。
//所以本题就是找到可以将树分成两个和尽量相近的子树的结点。 
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
		
		/*深度优先搜索所有树节点，对于每次递归中的root结点都进行求和操作，如果求得的和小于sum的一半，则停止求和，因为
		 接下来子节点的求和肯定都比这个数小。 
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
