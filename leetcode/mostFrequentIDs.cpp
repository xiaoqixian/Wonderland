// Date:   Sun Mar 24 10:59:37 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <cassert>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
using vector = std::vector<T>;

class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        const int n = nums.size();
        using freq_t = long long;
        std::unordered_map<int, freq_t> id_freq;
        std::map<freq_t, std::unordered_set<int>> freq_set;
        std::vector<freq_t> res(n);

        for (int i = 0; i < n; ++i) {
            const int id = nums[i];
            auto f = id_freq.find(id);

            if (f == id_freq.end()) {
                assert(freq[i] >= 0);
                id_freq.insert({ id, (freq_t)freq[i] });

                auto freq_f = freq_set.find((freq_t)freq[i]);
                if (freq_f == freq_set.end()) {
                    freq_set.insert({ (freq_t)freq[i], { id } });
                } else {
                    freq_f->second.insert(id);
                }

                res[i] = freq_set.rbegin()->first;
            } else {
                auto const old_id_freq = f->second;
                f->second += freq[i];

                auto freq_group = freq_set.find(old_id_freq);
                assert(freq_group != freq_set.end());

                freq_group->second.erase(id);
                if (freq_group->second.empty()) {
                    freq_set.erase(old_id_freq);
                }

                auto id_freq_new_group = freq_set.find(f->second);
                if (id_freq_new_group == freq_set.end()) {
                    freq_set.insert({ f->second, { id } });
                } else {
                    id_freq_new_group->second.insert(id);
                }

                res[i] = freq_set.rbegin()->first;
            }
        }
        return res;
    }
};
