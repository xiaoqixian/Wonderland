/**********************************************
  > File Name		: merge.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Jul  1 20:54:18 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        map<int, int> m;
        vector<vector<int>> res;

        for (auto v: intervals) {
            if (m.empty()) {
                m.insert({v[0], v[1]});
                continue;
            }
            map<int, int>::iterator iter = m.lower_bound(v[0]);

            if (iter == m.begin()) {//front
                if (iter->first > v[1]) {
                    m.insert({v[0], v[1]});
                    continue;
                }

                auto end = iter;
                while (end != m.end() && end->first <= v[1])
                    end++;

                end--;
                int r = v[1] > end->second ? v[1] : end->second;

                m.erase(iter, ++end);
                m.insert({v[0], r});

            } else if (iter == m.end()) {//rear
                iter--;
                if (v[0] > iter->second) {
                    m.insert({v[0], v[1]});
                } else if (v[1] > iter->second) {
                    int l = iter->first;
                    m.erase(iter);
                    m.insert({l, v[1]});
                }

            } else {//middle
                int l = v[0], r = v[1];
                iter--;
                if (iter->second < v[0])
                    iter++;
                else
                    l = iter->first;

                auto end = iter;
                while (end != m.end() && end->first <= v[1])
                    end++;

                end--;
                r = v[1] > end->second ? v[1] : end->second;

                m.erase(iter, ++end);
                m.insert({l, r});
            }
        }

        for (auto iter = m.begin(); iter != m.end(); iter++)
            res.push_back({iter->first, iter->second});

        return res;
    }
};

int main() {}
