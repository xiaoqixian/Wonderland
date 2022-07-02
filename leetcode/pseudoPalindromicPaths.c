/*
 Leetcode: 1457. 二叉树中的伪回文路径
 https://leetcode-cn.com/problems/pseudo-palindromic-paths-in-a-binary-tree/comments/
 */
 
#include <stdio.h>
 
struct TreeNode {
 	int val;
 	struct TreeNode* left;
 	struct TreeNode* right;
};

void traverse(struct TreeNode* root, int arr[], int* res);
void print_arr(int arr[], int n);

int res = 0;
int pseudoPalindromicPaths (struct TreeNode* root){
	int arr[9] = {0};
	traverse(root, arr, &res);
	return res;
}

void traverse(struct TreeNode* root, int arr[], int* res) {
	if (root == NULL) {
		return ;
	}
	arr[root->val]++;
	if (root->left == root->right) { //both equals to NULL
		print_arr(arr, 9);
		if (isPalindrome(arr, 9) == 1) {
			(*res)++;
		}
		arr[root->val]--;
		return ;
	}
	if (root->left != NULL) {
		printf("left node\n");
		traverse(root->left, arr, res);
	}
	if (root->right != NULL) {
		printf("right node\n");
		traverse(root->right, arr, res);
	}
}

int isPalindrome(int arr[], int n) {
	int i;
	int res = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] % 2 == 1) {
			res++;
		}
	}
	if (res > 1) {
		return 0;
	}
	return 1;
}

int main() {
	return 0;
}
