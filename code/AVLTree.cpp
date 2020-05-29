/*
 AVL树
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	int height;
	//char* str;
	TreeNode* left;
	TreeNode* right;
};

class AVLTree {
	private:
		TreeNode* root;
		
		TreeNode* rotateLeft(TreeNode* node) {
			//左旋操作 
			TreeNode* tmp = node->right;
			node->right = tmp->left;
			tmp->left = node;
			//更新结点高度 
			//先更新node结点的高度
			updateNodeHeight(node);
			//再更新tmp，也就是新的根节点 的高度 
			updateNodeHeight(tmp);
			return tmp;
		}
		
		TreeNode* rotateRight(TreeNode* node) {
			TreeNode* tmp = node->left;
			node->left = tmp->right;
			tmp->right = node;
			
			updateNodeHeight(node);
			updateNodeHeight(tmp);
			return tmp;
		}
		
		void updateNodeHeight(TreeNode* node) {
			int max = 0;
			if (node->left != NULL && node->left->height > max) {
				max = node->left->height;
			}
			if (node->right != NULL && node->right->height > max) {
				max = node->right->height;
			}
			node->height = max + 1;
		}
		
		int getNodeHeight(TreeNode* node) {
			if (node == NULL) {
				return 0;
			}
			return node->height;
		}
		
		TreeNode* _insert(TreeNode* node, int val) {
			if (node == NULL) {
				node = (TreeNode*)malloc(sizeof(TreeNode));
				if (node == NULL) {
					printf("allocate memory to new node failed\n");
					return NULL;
				}
				node->val = val;
				node->height = 1;
				node->left = NULL;
				node->right = NULL;
				return node;
			}
			int tmp = val - node->val;
			if (tmp < 0) {
				//printf("insert left node\n");
				//递归调用插入左子树 
				node->left = _insert(node->left, val);
				//判断两子树高度差是否超过1
				//若超过1，则需要通过进行旋转进行调整
				if (getNodeHeight(node->left) - getNodeHeight(node->right) > 1) {
					//如果是插在左子树的右边，则左子树需要先进行左旋 
					if (val > node->left->val) {
						node->left = rotateLeft(node->left);
					}
					node = rotateRight(node);
				}
			}
			else if (tmp > 0) {
				//printf("insert right node\n");
				node->right = _insert(node->right, val);
				if (getNodeHeight(node->right) - getNodeHeight(node->left) > 1) {
					if (val < node->right->val) {
						node->right = rotateRight(node->right);
					}
					node = rotateLeft(node);
				}
			}
			else {
				return node;//AVL树不支持相同元素的存在
			}
			updateNodeHeight(node);
			return node;
		}
		
		TreeNode* _remove(TreeNode* node, int val) {
			if (node == NULL) {
				printf("node %d not found\n", val);
				return node;
			}
			else if (val < node->val) {
				node->left = _remove(node->left, val);
				
				if (getNodeHeight(node->right) - getNodeHeight(node->left) > 1) {
					if (getNodeHeight(node->right->left) > getNodeHeight(node->right->right)) {
						node->right = rotateRight(node->right);
					}
					node = rotateLeft(node);
				}
			}
			else if (val > node->val) {
				node->right = _remove(node->right, val);
				
				if (getNodeHeight(node->left) - getNodeHeight(node->right) > 1) {
					if (getNodeHeight(node->left->right) > getNodeHeight(node->left->left)) {
						node->left = rotateLeft(node->left);
					}
					node = rotateRight(node);
				}
			}
			//如果当前节点是要删除的结点 
			else {
				//如果当前结点是叶子结点，则直接释放内存，树的平衡问题留给父结点去做。 
				if (node->left == NULL && node->right == NULL) {
					free(node);
					return NULL;
				}
				//如果当前结点只有右子树，则根据AVL树的平衡原理，右子树只有一个结点，否则与左子树的高度之差超过了1
				//所以可以直接左旋后进行释放，而右子节点依然处于底层，高度不变 
				else if (node->left == NULL) {
					TreeNode* tmp = node->right;
					free(node);
					return tmp;
				}
				//左子树同理
				else if (node->right == NULL) {
					TreeNode* tmp = node->left;
					free(node);
					return tmp; 
				}
				/*如果当前结点两个子树均存在，则直接从子树中"借"结点，说是借，其实是直接复制子结点的值，然后递归调用 
				  _remove函数从子树中删除子结点。
				  由于删除一个结点最多只会使得子树的高度减一，所以删除高度较高的子树中的结点最多只会导致两树的高度相
				  差为1，并不会导致平衡树失衡，也就不需要重新调整AVL树。
				  如果两个子树高度相同，则默认选择右子树中结点。				
				 */ 
				else {
					if (getNodeHeight(node->right) >= getNodeHeight(node->left)) {
						node->val = node->right->val;
						node->right = _remove(node->right, node->val);
					}
					else {
						node->val = node->left->val;
						node->left = _remove(node->left, node->val);
					}
					updateNodeHeight(node);
					return node;
				} 
			}
			updateNodeHeight(node);
			return node;
		}
	public:
		AVLTree() {
			root = NULL;
		}
		
		void insert(int val) {
			root = _insert(root, val);
		}
		
		void remove(int val) {
			root = _remove(root, val);
		}
		
		void printBinaryTree() {
			if (root == NULL) {
				printf("the tree is empty");
				return ;
			}
			TreeNode* tmp;
			queue<TreeNode*> q;
			q.push(root);
			int column = 1, count = 0, maxDepth = 1 << (root->height - 1);
			//printf("max depth%d\n", maxDepth);
			const int state = 0;
			TreeNode* null = (TreeNode*)&state;//如果树的某个子节点为NULL，则将这个指针压入队列，以便识别空节点。 
			while (!q.empty() && column <= maxDepth) {
				tmp = q.front();
				q.pop();
				//printf("pop one\n");
				count++;
				if (null == tmp) {
					printf("null ");
					q.push(null);
					q.push(null);
					if (count == column) {
						count = 0;
						column <<= 1;
						printf("\n");
					}
					continue;
				}
				else {
					printf("%d ", tmp->val);
				}
				if (tmp->left == NULL) {
					q.push(null);
				}
				else {
					q.push(tmp->left);
				}
				if (tmp->right == NULL) {
					q.push(null);
				}
				else {
					q.push(tmp->right);
				}
				if (count == column) {
					count = 0;
					column <<= 1;
					printf("\n");
				}
			}
		}
}; 

int main() {
	AVLTree tree;
	int nums[] = {4,6,8,2,1,5,7,9};
	int i, len = sizeof(nums)/sizeof(int);
	for (i = 0; i < len; i++) {
		tree.insert(nums[i]);
		//printf("insert one\n");
	}
	tree.printBinaryTree();
	tree.remove(4);
	tree.printBinaryTree();
	return 0;
}
