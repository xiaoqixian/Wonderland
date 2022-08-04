/**********************************************
  > File Name		: spiralMatrix.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug  3 15:58:41 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<vector<int>> spiralMatrix(const int m, const int n, ListNode* head) {
        vector<vector<int>> res(m, vector<int>(n, -1));
        char directions[4] = {'r', 'd', 'l', 'u'};
        int r = 0, c = 0, dd = 0;

        while (head != nullptr) {
            res[r][c] = head->val;
            head = head->next;
            
            switch (directions[dd]) {
                case 'r':
                    c++;
                    if (c >= n || res[r][c] != -1) {
                        c--; r++;
                        dd++; dd %= 4;
                    } break;
                case 'd':
                    r++;
                    if (r >= m || res[r][c] != -1) {
                        r--; c--;
                        dd++; dd %= 4;
                    } break;
                case 'l':
                    c--;
                    if (c < 0 || res[r][c] != -1) {
                        c++; r--;
                        dd++; dd %= 4;
                    } break;
                case 'u':
                    r--;
                    if (r < 0 || res[r][c] != -1) {
                        r++; c++;
                        dd++; dd %= 4;
                    } break;
            }
        }
        return res;
    }
};
