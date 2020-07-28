/**********************************************
  > File Name		: countPairs.cpp
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 26 Jul 2020 11:14:11 AM CST
 ************************************************/

#include <iostream>
using namespace std;

/*
 任意两个叶子节点的距离等于它们到它们的公共父节点的距离之和。

 干脆不考虑什么重复的问题，结果出来除以2就解决了。
 */
class Solution {
public:
    int countPairs(TreeNode* root, int distance) {
        //先找到所有的叶子节点，由于知道父节点与叶子节点的索引关系，所以非常好找
        //由于是通过节点给出的树，所以需要先转化为数组
        queue<TreeNode*> q;
        q.push(root);
        vector<bool> v;
        while (!q.empty()) {
            TreeNode* tmp = q.top();
            q.pop();
            if (tmp == NULL) {
                v.push_back(false);
                continue;
            }
            v.push_back(true);
            q.push(tmp->left);
            q.push(tmp->right);
        }
        int size = v.size();
        vector<int> leafIndex;
        for (int i = 0; i < size; i++) {
            if (!v[i]) continue;
            int lchild = 2*i+1, rchild = 2*i+2;
            if (lchild >= size) {
                leafIndex.push_back(i);
                continue;
            }
            if (!v[lchild] and !v[rchild]) {
                leafIndex.push_back(i);
            }
        }
        int res = 0;
        for (int i = 0; i < leafIndex.size(); i++) {
            for (int j = 0; j < leafIndex.size(); j++) {
                if (i == j) {
                    continue;
                }
                if (calcDistance(i, j) <= distance) {
                    res++;
                }
            }
        }
        return res/2;
    }

    int calcDistance(int i, int j) {
        //找到i和j的公共父节点，计算走过的距离之和
        int res = 0;
        while (i != j) {
            while (i > j) {
                i = (--i)/2;
                res++;
            }
            if (i == j) {
                return res;
            }
            while (j > i) {
                j = (--j)/2;
                res++;
            }
        }
        return res;
    }
};
