// Date:   Sun Mar 24 11:26:48 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iterator>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using std::vector;
using std::string;

struct DictionaryTree;
struct Index {
    size_t match_length;
    size_t word_length;
    size_t index;
    
    friend bool operator<(Index const& lhs, Index const& rhs) {
        if (lhs.match_length == rhs.match_length) {
            if (lhs.word_length == rhs.word_length) 
                return lhs.index < rhs.index;
            else 
                return lhs.word_length < rhs.word_length;
        } else {
            return lhs.match_length > rhs.match_length;
        }
    }
};

struct DictionaryTree {
    static const size_t RANGE = 26;
    std::array<DictionaryTree*, RANGE> tree { nullptr };

    bool stop;
    size_t index = std::numeric_limits<size_t>::max();
    size_t depth = 0;
    DictionaryTree* parent;

    DictionaryTree(): stop(false), parent(nullptr), depth(0) {}
    DictionaryTree(DictionaryTree* parent, size_t depth): stop(false), parent(parent), depth(depth) {}
    DictionaryTree(bool stop, size_t i, size_t depth, DictionaryTree* parent):
        stop(stop), index(i), parent(parent), depth(depth) {}

    void insert(string const& s, const size_t word_index) {
        auto level = this;
        size_t depth = 0;
        for (auto it = s.crbegin(); it != s.crend(); ++it) {
            const char index = *it - 'a';
            ++depth;
            if (level->tree[index] == nullptr) {
                level->tree[index] = new DictionaryTree(level, depth);
            }
            level = level->tree[index];
        }

        level->index = std::min(level->index, word_index);
        level->stop = true;
    }

    Index match(string const& s) {
        auto level = this;
        for (auto it = s.crbegin(); it != s.crend(); ++it) {
            level = level->tree[*it - 'a'];
            if (level == nullptr) {
                level = level->parent;
                break;
            }
        }

        const size_t match_len = level->depth;

        std::queue<DictionaryTree*> queue;
        queue.push(level);

        Index res = {
            .match_length = match_len,
            .word_length = std::numeric_limits<size_t>::max(),
            .index = std::numeric_limits<size_t>::max()
        };

        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();

            if (node->stop) {
                if (node->depth < res.word_length) {
                    res.word_length = node->depth;
                    res.index = node->index;
                } 
                else if (node->depth == res.word_length && node->index < res.index) {
                    res.index = node->index;
                }
            } 
            else if (node->depth < res.word_length) {
                for (auto i = 0; i < RANGE; ++i) {
                    if (node->tree[i] != nullptr) 
                        queue.push(node->tree[i]);
                }
            }
        }
        
        assert(res.word_length != std::numeric_limits<size_t>::max());
        assert(res.index != std::numeric_limits<size_t>::max());
        return res;
    }

    ~DictionaryTree() {
        for (auto i = 0; i < RANGE; ++i) {
            if (this->tree[i] != nullptr) {
                delete this->tree[i];
            }
        }
    }
};

class Solution {
public:
    static int match_suffix(string const& lhs, string const& rhs) {
        int res = 0;
        auto lit = lhs.crbegin(), rit = rhs.crbegin();
        while (true) {
            if (lit == lhs.crend() || rit == rhs.crend() || *lit != *rit) 
                break;

            ++res;
            ++lit; 
            ++rit;
        }
        return res;
    }
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        const size_t n = wordsQuery.size();
        vector<int> res(n);
        
        // build a DictionaryTree 
        DictionaryTree dict_tree;
        for (auto i = 0; i < wordsContainer.size(); ++i) {
            dict_tree.insert(wordsContainer[i], i);
        }

        for (auto i = 0; i < n; ++i) {
            auto match = dict_tree.match(wordsQuery[i]);
            res[i] = match.index;
        }

        return res;
    }
};

int main() {
    Index lhs { 2, 4, 0 }, rhs { 2, 3, 1 };
    assert(rhs < lhs);
}
