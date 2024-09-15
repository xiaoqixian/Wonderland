// Date:   Sun Sep 15 10:51:09 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <array>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;
using std::string_view;

auto init_ = [] {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    return 0;
}();

struct Node {
    std::array<Node*, 26> next = { nullptr };
};

struct DictTree {
    Node* root;
    DictTree(): root(new Node()) {}
    void insert(string const& word) {
        Node* curr = root;
        for (char c: word) {
            const int i = c - 'a';
            auto& next = curr->next;
            if (next[i] == nullptr) {
                next[i] = new Node();
            }
            curr = next[i];
        }
    }
};

class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        const int n = words.size();
        // vector<string> prefixes;
        DictTree tree;
        for (auto const& word: words) {
            tree.insert(word);
        }
        // printf("insert done\n");

        vector<int> dp(target.length(), INT_MAX);
        const int tl = target.length();
        for (int i = 0; i < tl; i++) {
            Node* curr = tree.root;
            const int cnt = (i == 0 ? 0 : dp[i-1]) + 1;
            // printf("i = %d, cnt = %d\n", i, cnt);
            for (int j = i; j < tl; j++) {
                const int i = target[j] - 'a';
                auto const& next = curr->next;
                if (next[i] != nullptr) {
                    dp[j] = std::min(dp[j], cnt);
                    curr = next[i];
                } else break;
            }

            if (dp[i] == INT_MAX) break;
        }
        return dp[tl-1] == INT_MAX ? -1 : dp[tl-1];
    }
};

int main() {
    vector<string> words = {"b","ccacc","a"};
    string target = "cccaaaacba";
    printf("%d\n", Solution().minValidStrings(words, target));
}
