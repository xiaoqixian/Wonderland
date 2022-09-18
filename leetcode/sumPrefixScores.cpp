/**********************************************
  > File Name		: sumPrefixScores.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep 18 11:07:17 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class DictTree {
private:
    struct Row {
        uint16_t times[26];
        Row* next[26];
    };

    Row* root;
public:
    DictTree() {
        this->root = new Row();
    }

    void insert(string s) {
        Row* level = this->root;
        for (char c: s) {
            int index = c - 'a';
            level->times[index]++;
            
            if (level->next[index] == nullptr) {
                level->next[index] = new Row();
            }

            level = level->next[index];
        }
    }

    int score(string s) {
        Row* level = this->root;
        int res = 0;
        for (char c: s) {
            int index = c - 'a';
            res += level->times[index];
            level = level->next[index];
        }
        return res;
    }
};

class Solution {
public:
    vector<int> sumPrefixScores(const vector<string>& words) {
        vector<int> res(words.size());
        DictTree dt;

        for (const string& w: words) {
            dt.insert(w);
        }

        auto it = res.begin();
        for (const string& w: words) {
            *it = dt.score(w);
            it++;
        }

        return res;
    }
};

int main() {
    vector<string> words = {"xltanjohvw","xltanjohk","cogsbyuq","nlthmiqzk","pluliugjsp","nzyoghv","pluliugjsu","xltanjohvn"};
    Solution().sumPrefixScores(words);
}
