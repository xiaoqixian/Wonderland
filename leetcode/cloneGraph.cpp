/**********************************************
  > File Name		: cloneGraph.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul  3 17:37:25 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> m;

        return cloneNode(node, m);
    }

    Node* cloneNode(Node* node, unordered_map<Node*, Node*>& m) {
        auto iter = m.find(node);
        if (iter != m.end())
            return iter->second;

        Node* newNode = new Node(node->val);
        m.insert({node, newNode});

        for (auto neighborNode: node->neighbors) {
            newNode->neighbors.push_back(cloneNode(neighborNode, m));
        }
        return newNode;
    }
};
