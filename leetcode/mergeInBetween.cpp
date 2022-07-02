/**********************************************
  > File Name		: mergeInBetween.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 13 Feb 2022 12:02:54 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>

 //Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* fake_head = new ListNode(0, list1), *start = fake_head, *end = nullptr;
        
        while (a--) start = start->next;

        ListNode* end = start->next;
        start->next = list2;

        int len = b - a;
        while (end != nullptr && len--) {
            end = end->next;
        }

        ListNode* temp = list2;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = end;
        return fake_head->next;
    }
};
