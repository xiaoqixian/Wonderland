/**********************************************
  > File Name		: reverseKGroup.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 24 Dec 2021 09:25:41 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stack>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    static ListNode* build_list(vector<int>& nums) {
        ListNode* head = new ListNode;
        ListNode* iter = head;

        for (int i: nums) {
            iter->next = new ListNode(i);
            iter = iter->next;
        }
        return head->next;
    }

    void print_list() {
        ListNode* head = this;
        printf("%d", head->val);
        head = head->next;

        while (head != nullptr) {
            printf("->%d", head->val);
            head = head->next;
        }
        printf("\n");
    }
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        stack<ListNode*> s;
        queue<ListNode*> q;
        ListNode* start = head, *iter, *remains;
        int count;
        
        while (iter != nullptr) {
            count = k;
            iter = start;
            //printf("start = %d\n", iter == nullptr ? -250 : iter->val);

            while (iter != nullptr && count) {
                s.push(iter);
                //printf("s push %d\n", iter->val);
                iter = iter->next;
                count--;
            }

            if (count) {
                remains = start;
                break;
            } else {
                start = iter;
                while (!s.empty()) {
                    q.push(s.top());
                    //printf("q push %d\n", s.top()->val);
                    s.pop();
                }
            }
        }

        head = q.front();
        //printf("head = %d\n", head->val);
        q.pop();
        iter = head;
        while (!q.empty()) {
            iter->next = q.front();
            iter = iter->next;
            q.pop();
        }
        iter->next = remains;

        return head;
    }
};


int main() {
    vector<int> nums;
    for (int i = 0; i < 10000; i++) {
        nums.push_back(i);
    }
    ListNode* list = ListNode::build_list(nums);
    //list->print_list();
    Solution s;
    list = s.reverseKGroup(list, 5);
    list->print_list();
}
