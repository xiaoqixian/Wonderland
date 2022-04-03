/**********************************************
  > File Name		: StreamChecker.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 03 Apr 2022 10:39:33 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SuffixTree {
public:
    struct Node {
        vector<Node*> next;
        bool end;

        Node(): end(false), next(vector<Node*>(26, nullptr)) {}
    };

    Node* root;

    SuffixTree() {}

    SuffixTree(vector<string>& words) {
        this->root = new Node();
        for (string& word: words) {
            this->push(word);
            cout << "put " << word << endl;
        }
    }

    void push(string& word) {
        if (word.size() == 0)
            return;
        
        Node* temp = this->root;
        int index;
        for (int i = word.size()-1; i != -1; i--) {
            index = word[i] - 'a';
            if (temp->next[index] == nullptr) {
                temp->next[index] = new Node();
            }
            temp = temp->next[index];
        }
        temp->end = true;
    }
};

class StreamChecker {
private:
    SuffixTree st;
    vector<char> stream;
public:
    StreamChecker(vector<string>& words) {
        this->st = SuffixTree(words);
        this->stream = vector<char>();
    }
    
    bool query(char letter) {
        this->stream.push_back(letter);
        int i = this->stream.size(); 
        SuffixTree::Node* temp = this->st.root;

        while (--i >= 0 && temp != nullptr) {
            temp = temp->next[this->stream[i] - 'a'];
            if (temp != nullptr && temp->end)
                return true;
        }
        return false;
    }
};

int main() {
    vector<string> words = {"cd", "f", "kl"};
    StreamChecker sc(words);
    cout << sc.query('a') << endl;
    cout << sc.query('c') << endl;
    cout << sc.query('d') << endl;
}

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
