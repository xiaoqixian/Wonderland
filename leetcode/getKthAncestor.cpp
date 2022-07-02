/**********************************************
  > File Name		: getKthAncestor.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 16 Dec 2021 10:57:28 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <cassert>
using namespace std;

class Node {
public:
    int parent;
    int val;
    vector<int> children;

    Node(int val, int parent) {
        this->parent = parent;
        this->val = val;
        this->children = vector<int>();
    }

    void build(vector<Node>& nodes, vector<vector<int>>& ancestors) {
        assert(ancestors[this->val].size() == 0);
        vector<int>& path = ancestors[this->val];
        path.push_back(this->parent);
        
        if (this->parent != -1 && ancestors[this->parent].size() == 0) {
            nodes[this->parent].build(nodes, ancestors);
        }

        for (int num: ancestors[this->parent]) {
            path.push_back(num);
        }

        //for (int num: this->children) {
            //nodes[num].build(nodes, ancestors);
        //}
    }
};

class TreeAncestor {
private:
    vector<Node> nodes;
    vector<vector<int>> ancestors; //ancestors[i][k] records ith node's kth ancestor.
public:
    TreeAncestor(int n, vector<int>& parent) {
        for (int i = 0; i < n; i++) {
            this->nodes.push_back(Node(i, parent[i]));
            if (parent[i] < 0) {
                continue;
            }
            this->nodes[parent[i]].children.push_back(i);
            //this->ancestors.push_back(vector<int>(i+1, -1));
            //this->ancestors[i][1] = parent[i];
            //this->ancestors[i][0] = i;
        }
        this->ancestors = vector<vector<int>>(n, vector<int>());
    }

    int getKthAncestor(int node, int k) {
        if (k == 0) {
            return node;
        }
        if (node == 0) {
            return -1;
        }

        if (this->ancestors[node].size() == 0) {
            this->nodes[node].build(this->nodes, this->ancestors);
        }
        if (k > this->ancestors[node].size()) {
            return -1;
        }
        return this->ancestors[node][k-1];
    }
    
/*    int getKthAncestor(int node, int k) {*/
        /*if (k == 0) {*/
            /*return node;*/
        /*}*/
        /*if (k > node) {*/
            /*return -1;*/
        /*}*/
        /*int temp = this->ancestors[node][k];*/
        /*if (temp >= 0) {*/
            /*return temp;*/
        /*} else if (temp == -2) {//-2 means unreachable.*/
            /*return -1;*/
        /*}*/

        /*int origin = node, step = 0;*/
        /*vector<int> path = {node};*/
        /*while (step < k && this->nodes[node].parent != -1) {*/
            /*node = this->nodes[node].parent;*/
            /*temp = ++step;*/
            /*for (int n: path) {*/
                /*this->ancestors[n][temp--] = node;*/
            /*}*/
            /*path.push_back(node);*/
        /*}*/
        /*if (step < k) {*/
            
        /*}*/
        /*return node;*/
    /*}*/
};

/*
 * Binary Lifting Solution
 * 作者：liuyubobobo
 * 链接：https://leetcode-cn.com/problems/kth-ancestor-of-a-tree-node/solution/li-kou-zai-zhu-jian-ba-acm-mo-ban-ti-ban-shang-lai/ 
 * 来源：力扣（LeetCode） 
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */
class TreeAncestor {

private:
    vector<vector<int>> dp;

public:
    TreeAncestor(int n, vector<int>& parent) : dp(n) {

        for(int i = 0; i < n; i ++)
            dp[i].push_back(parent[i]);

        for(int j = 1; ; j ++){
            bool allneg = true;
            for(int i = 0; i < n; i ++){
                int t = dp[i][j - 1] != -1 ? dp[dp[i][j - 1]][j - 1] : -1;
                dp[i].push_back(t);
                if(t != -1) allneg = false;
            }
            if(allneg) break; // 所有的节点的 2^j 的祖先都是 -1 了，就不用再计算了
        }
    }

    int getKthAncestor(int node, int k) {

        if(k == 0 || node== -1) return node;

        int pos = ffs(k) - 1; // C++ 语言中 ffs(k) 求解出 k 的最右侧第一个 1 的位置（1-based）

        return pos < dp[node].size() ? getKthAncestor(dp[node][pos], k - (1 << pos)) : -1;
    }
};


/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

int main() {
    vector<int> parent = {-1, 0, 0, 1, 1, 2, 2};
    TreeAncestor* ta = new TreeAncestor(7, parent);
    printf("%d\n", ta->getKthAncestor(3, 1));
    printf("%d\n", ta->getKthAncestor(5, 2));
    printf("%d\n", ta->getKthAncestor(6, 3));
}
