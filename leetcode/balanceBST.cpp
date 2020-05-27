/*
 Leetcode: 1382.將二叉搜索树变平衡 
 */
 
#include <stdio.h>
#include <vector>
#include <map>
#include <stack>
#include <stdlib.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

/*
 解1：中序遍历二叉搜索树，得到一个数组。然后递归重新构造一个平衡树，乃本题之最优解 
 */ 

class Solution {
	private:
		TreeNode res;
	public:
		TreeNode* balanceBST(TreeNode* root) {
			vector<int> buffer;
			search(root, buffer);
			return build(buffer, 0, buffer.size() - 1);
		}
		
		TreeNode* build(vector<int> buffer, int i, int j) {
			if (i > j) {
				return NULL;
			}
			if (i == j) {
				res.val = buffer[0];
				return &res;
			}
			int m = i + (j - i)/2;
			res.val = buffer[m];
			res.left = build(buffer, i, m - 1);
			res.right = build(buffer, m + 1, j);
			return &res;
		}
		
		void search(TreeNode* root, vector<int> buffer) {
			if (root == NULL) {
				return ;
			}
			search(root->left, buffer);
			buffer.push_back(root->val);
			search(root->right, buffer);
		}
};

/*
 解2:一开始就构造一棵平衡树，一边遍历原树，一边将树中节点插入平衡树中。 
 */ 
 
class Solution2 {
	private:
		TreeNode res;
	public:
		TreeNode* balanceBST(TreeNode* root) {
			if (root == NULL || (root->left == NULL && root->right == NULL)) {
				return root;
			}
			//先序遍历原树，节点插入新树中
			map<TreeNode*, int> height;
			stack<TreeNode*> nodeStack;
			nodeStack.push(root);
			TreeNode* res = NULL, *tmp = NULL;
			while (!nodeStack.empty()) {
				tmp = nodeStack.top();
				nodeStack.pop();
				if (tmp->right != NULL) {
					nodeStack.push(tmp->right);
				}
				if (tmp->left != NULL) {
					nodeStack.push(tmp->left);
				}
				res = insert(res, tmp->val, height);
			}
			return res;
		}
		
		//插入新节点，返回可能已经发生了左旋或右旋后的根节点 
		TreeNode* insert(TreeNode* root, int val, map<TreeNode*, int> height) {
			if (root == NULL) {
				root = (TreeNode*)malloc(sizeof(TreeNode));
				root->val = val;
				height.insert(pair<TreeNode*, int>(root, 1));
				return root;
			}
			int comp = val - root->val;
			if (comp < 0) {
				root->left = insert(root->left, val, height);
				int left_node_height, right_node_height;
				left_node_height = getNodeHeight(root->left, height);
				right_node_height = getNodeHeight(root->right, height);
				if (left_node_height - right_node_height > 1) {
					if (val > root->left->val) {
						root->left = rotateLeft(root->left, height);
					}
					root = rotateRight(root, height);
				}
			}
			else if (comp > 0) {
				root->right = insert(root->right, val, height);
				int left_node_height, right_node_height;
				left_node_height = getNodeHeight(root->left, height);
				right_node_height = getNodeHeight(root->right, height);
				if (right_node_height - left_node_height > 1) {
					if (val < root->right->val) {
						root->right = rotateRight(root->right, height);
					}
					root = rotateLeft(root, height);
				}
			}
			else {
				return root;
			}
			int root_height = getNodeHeight(root, height);
			height.insert(pair<TreeNode*, int>(root, root_height));
			return root;
		}
		
		TreeNode* rotateLeft(TreeNode* root, map<TreeNode*, int> height) {
			//左旋 
			if (root == NULL || root->right == NULL) {
				return root;
			}
			TreeNode* right = root->right;
			root->right = right->left;
			right->left = root;
			
			//更新节点高度
			int new_root_height, new_right_height;
			new_root_height = getNodeHeight(root, height);
			height.insert(pair<TreeNode*, int>(root, new_root_height));
			int tmp = getNodeHeight(right->right, height);
			new_right_height = tmp > new_root_height ? (tmp + 1) : (new_root_height);
			height.insert(pair<TreeNode*, int>(right, new_right_height));
			return right;
		}
		
		TreeNode* rotateRight(TreeNode* root, map<TreeNode*, int> height) {
			//右旋
			if (root == NULL || root->left == NULL) {
				return root;
			}
			TreeNode* left = root->left;
			root->left = left->right;
			left->right = root;
			 
			//更新高度
			int new_root_height, new_left_height;
			new_root_height = getNodeHeight(root, height);
			height.insert(pair<TreeNode*, int>(root, new_root_height));
			int tmp = getNodeHeight(left, height);
			new_left_height = tmp > new_root_height ? (tmp + 1) : (new_root_height);
			height.insert(pair<TreeNode*, int>(left, new_left_height));
			return left;
		}
		
		int getNodeHeight(TreeNode* node, map<TreeNode*, int> height) {
			map<TreeNode*, int>::iterator left_iter, right_iter;
			int left_height, right_height;
			if (node->left) {
				left_iter = height.find(node->left);
				left_height = left_iter->second;
			}
			else {
				left_height = 0;
			}
			if (node->right) {
				right_iter = height.find(node->right);
				right_height = right_iter->second;
			}
			else {
				right_height = 0;
			}
			return (left_height > right_height ? (left_height + 1) : (right_height + 1));
		}
}; 

int main() {
	int s = 1 << 1;
	printf("%d\n", s);
	return 0;
}
