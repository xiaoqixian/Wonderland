/**********************************************
  > File Name		: searchMatrix.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Jul  1 16:47:45 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size(), len = m * n;
        int l = 0, r = len-1;

        while (l <= r) {
            int mid = (l + r) >> 1;
            int cur = matrix[mid / n][mid % n];
            
            if (cur == target) {
                return true;
            } else if (cur < target) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return false;
    }
};

int main() {}
