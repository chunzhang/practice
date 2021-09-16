/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Iterative approach
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr;
        while(head) {
            ListNode *next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};

// My try of recursive approach, which is just a rewrite of iterative approach
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return helper(nullptr, head);
    }
    
private:
    ListNode* helper(ListNode *prev, ListNode *cur) {
        if(!cur)
            return prev;
        ListNode *next = cur->next;
        cur->next = prev;
        return helper(cur, next);
    }
};

// A better recursive solution
// -- Key is to work backward
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode *newHead = reverseList(head->next);
        // Now we have something like head-->n1 <-- n2 <-- n3 <-- ... <-- newHead
        // And head->next is the tail of the already reversed list
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
