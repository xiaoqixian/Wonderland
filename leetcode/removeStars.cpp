/**********************************************
  > File Name		: removeStars.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug 28 11:09:30 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <list>
using namespace std;

class Solution {
public:
    string removeStars(string s) {
        struct Range {
            int left, right;
            Range(int left, int right): left(left), right(right) {}

            inline int size() const {
                return this->right - this->left + 1;
            }
        };

        list<Range> l;
        l.push_back(Range(0, s.size()-1));
        
        auto it = l.begin();
        int pos = 0;

        while (pos < s.size()) {
            if (s[pos] != '*') {
                pos++;
                continue;
            }

            if (pos == it->left) {
                auto prev = it;
                assert(prev != l.begin()); prev--;

                if (prev->size() == 1) {
                    l.erase(prev);
                } else {
                    prev->right--;
                }

                it->left++;
                pos++;
                continue;
            }

            if (pos == it->left + 1) {
                it->left += 2;
            } else if (pos == it->right) {
                it->right -= 2;
            } else {
                l.insert(it, Range(it->left, pos-2));
                l.insert(it, Range(pos+1, it->right));
                it = l.erase(it); assert(it == l.end());
                it--;
            }

            pos++;
        }

        string res = "";

        for (auto it = l.cbegin(); it != l.cend(); it++) {
            res += s.substr(it->left, it->size());
        }
        return res;
    }
};

#include <iostream>
int main() {
    cout << Solution().removeStars("erase*****") << endl;
}
