/**********************************************
  > File Name		: Codec.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 23 Mar 2022 03:59:58 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <string.h>
#include <queue>
#include <iostream>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Codec {
private:
    queue<TreeNode*> q;
    char* cache;
    size_t capacity;
    static const char seperator = ',';
    static const char nullptrSymbol = 'n';
    //unordered_map<string, TreeNode*> deser_map;
    //unordered_map<TreeNode*, string> ser_map;
public:
    Codec() {
        this->q = queue<TreeNode*>();
        this->capacity = 128;
        this->cache = new char[this->capacity];
        //this->deser_map = unordered_map<string, TreeNode*>();
        //this->ser_map = unordered_map<TreeNode*, string>();
    }

    static inline int getDigit(int val) {
        if (val == 0)
            return 1;
        int digit = 0;
        while (val) {
            digit++;
            val /= 10;
        }
        return digit;
    }

    void expand(const size_t& len) {
        //expand cache
        char* temp = this->cache;
        this->capacity <<= 1;
        this->cache = new char[this->capacity];
        memcpy(this->cache, temp, len);
        delete[] temp;
    }

    void putNumber(int val, size_t& len) {
        int digit = this->getDigit(val);

        if (len + digit + 1 >= this->capacity) {
            this->expand(len);
        }

        sprintf(this->cache + len, "%d,", val);
        len += (digit + 1);
    }

    inline void putNull(size_t& len) {
        if (len + 2 >= this->capacity)
            this->expand(len);
        sprintf(this->cache + len, "n,");
        len += 2;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr)
            return "";

        this->q.push(root);
        TreeNode* temp;
        size_t len = 0;
        int digit, val;

        this->putNumber(root->val, len);

        while (!this->q.empty()) {
            temp = this->q.front();
            this->q.pop();

            if (temp->left == nullptr) {
                this->putNull(len);
            } else {
                this->putNumber(temp->left->val, len);
                this->q.push(temp->left);
            }

            if (temp->right == nullptr) {
                this->putNull(len);
            } else {
                this->putNumber(temp->right->val, len);
                this->q.push(temp->right);
            }
        }
        //string ser_string(this->cache, len);
        //this->ser_map.insert({root, ser_string});
        //this->deser_map.insert({ser_string, root});
        return string(this->cache, len);
    }

    static int parseInt(int& left, string s) {
        int res = 0;
        while (s[left] != seperator) {
            res *= 10;
            res += s[left++] - '0';
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.length() == 0)
            return nullptr;

        int index = 0;
        TreeNode* root = new TreeNode(this->parseInt(index, data)), *temp;
        this->q.push(root);

        while (!this->q.empty()) {
            temp = this->q.front();
            this->q.pop();

            index++; //jump comma seperator
            if (data[index] != this->nullptrSymbol) {
                temp->left = new TreeNode(this->parseInt(index, data));
                this->q.push(temp->left);
            } else index++; //jump nullptrSymbol 'n'

            index++; //jump comma seperator again
            if (data[index] != this->nullptrSymbol) {
                temp->right = new TreeNode(this->parseInt(index, data));
                this->q.push(temp->right);
            } else index++; //jump nullptrSymbol 'n'
        }
        return root;
    }

    void showTree(TreeNode* root) {
        this->q.push(root);
        TreeNode* temp;

        while (!this->q.empty()) {
            temp = this->q.front();
            this->q.pop();
            cout << temp->val << ", ";
            if (temp->left != nullptr)
                this->q.push(temp->left);
            if (temp->right != nullptr)
                this->q.push(temp->right);
        }
        cout << endl;
    }
};

int main() {
    Codec ser;
    //TreeNode* root = new TreeNode(2, new TreeNode(1, new TreeNode(4), nullptr), new TreeNode(3, nullptr, new TreeNode(250)));
    TreeNode* root = new TreeNode(0);
    string serializeString = ser.serialize(root);
    cout << serializeString << endl;
    TreeNode* deserializedRoot = ser.deserialize(serializeString);
    ser.showTree(deserializedRoot);
}
