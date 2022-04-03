/**********************************************
  > File Name		: Trie.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 02 Apr 2022 04:26:03 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>

#include <iostream>
using namespace std;

class Trie {
private:
    struct Node {
        bool end;
        Node** next;

        Node(): end(false), next(new Node*[26]) {}

        ~Node() {
            delete[] this->next;
        }
    };

    Node* root;
    size_t size;

public:
    Trie() {
        this->root = new Node();
        this->size = 0;
        cout << sizeof(Node) << endl;
    }
    
    void insert(string word) {
        Node* temp = this->root;
        int index, len = word.size();
        for (int i = 0; i != len; i++) {
            index = word[i] - 'a';
            if (temp->next[index] == nullptr) {
                temp->next[index] = new Node();
            }
            if (i == len-1) {
                temp->next[index]->end = true;
            }
            temp = temp->next[index];
        }
    }
    
    bool search(string word) {
        Node* temp = this->root;
        int index;
        for (char c: word) {
            index = c - 'a';
            if (temp->next[index] == nullptr) {
                return false;
            }
            temp = temp->next[index];
        }
        return temp->end;
    }
    
    bool startsWith(string prefix) {
        Node* temp = this->root;
        int index;
        for (char c: prefix) {
            index = c - 'a';
            if (temp->next[index] == nullptr) {
                return false;
            }
            temp = temp->next[index];
        }
        return true;
    }
};

int main() {
    Trie t;
    t.insert("apple");
    cout << t.search("apple") << endl;
    cout << t.search("app") << endl;
    cout << t.startsWith("app") << endl;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
