/**********************************************
  > File Name		: smallestTrimedNumbers.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Jul 17 20:30:29 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

class Solution {
public:
    vector<int> smallestTrimmedNumbers(const vector<string>& nums, const vector<vector<int>>& queries) {
        vector<int> res = vector<int>(queries.size(), -1);
        vector<int> indices(nums.size());

        for (int i = 0; i < nums.size(); i++) {indices[i] = i;}

        auto it = res.begin();

        for (auto const& q: queries) {
            const int k = q[0] - 1, trim = q[1];
            
            sort(indices.begin(), indices.end(), [&](const int& i1, const int& i2) {
                
                const string& s1 = nums[i1];
                const string& s2 = nums[i2];
                const int l1 = s1.size(), l2 = s2.size();
                int index1 = l1 - trim, index2 = l2 - trim;
                
                while (index1 < l1 && s1[index1] == s2[index2]) {
                    index1++;
                    index2++;
                }

                if (index1 == l1) {
                    return i1 < i2;
                } else {
                    return s1[index1] < s2[index2];
                }
            });

            *it = indices[k];
            it++;
        }
        return res;
    }
};

int main() {
    vector<string> nums = {"102","473","251","814"};
    vector<vector<int>> queries = {{1,1},{2,3},{4,2},{1,2}};
    Solution().smallestTrimmedNumbers(nums, queries);
}
