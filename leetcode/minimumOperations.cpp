/**********************************************
  > File Name		: minimumOperations.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Jul 18 11:23:12 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<int> prime_list;
    
    void generate_prime(const int bound) {
        if (prime_list.empty()) {
            prime_list = {2,3,5,7,11,13,17,19,23,29};
        }

        if (prime_list.back() >= bound)
            return;

        int start = prime_list.back() + 2; //never two consecutive prime numbers except 1,2,3.
        while (start <= bound) {
            bool add = true;
            for (const int p: prime_list) {
                if (p > (start >> 1) || start % p == 0) {
                    add = false;
                    break;
                }
            }
            if (add) {
                prime_list.push_back(start);
                start++;
            }
            start++;
        }
    }
public:
    int minOperations(vector<int>& nums, const vector<int>& numsDivide) {
        sort(nums.begin(), nums.end());

        if (nums[0] == 0)
            return 0;

        unordered_map<int, vector<int>> um;

        for (const int nd: numsDivide) {
            generate_prime(min(nd >> 1, nums.back()));
            for (const int p: prime_list) {
                if (p > (nd >> 1))
                    break;
                if (nd % p == 0) {
                    auto it = um.find(p);
                    if (it == um.end()) {
                        um.insert({p, {nd}});
                    } else {
                        it->second.push_back(nd);
                    }
                }
            }
        }

        auto can_divide = [&](int p) {
            auto it = um.find(p);
            return it != um.end() && it->second.size() == numsDivide.size();
        };

        int prev = -1, i = 0;
        const int len = nums.size();
        while (i < len) {
            while (i < len && nums[i] == prev) i++;

            if (i == len) return -1;

            prev = nums[i];
            bool check = true;

            for (const int p: prime_list) {
                if (prev % p == 0 && !can_divide(p)) {
                    check = false;
                    break;
                }
            }

            if (check) {
                bool all = true;
                for (const int nd: numsDivide) {
                    if (nd % prev != 0) {
                        all = false;
                        break;
                    }
                }
                if (all) return i;
            }
        }

        return -1;
    }
};

int main() {
    vector<int> nums = {2,3,2,4,3}, numsDivide = {9,6,9,3,15};
    Solution().minOperations(nums, numsDivide);
}
