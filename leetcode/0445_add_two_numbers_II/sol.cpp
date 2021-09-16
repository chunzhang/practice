/*
  You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

  You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

  Example 1:


  Input: l1 = [7,2,4,3], l2 = [5,6,4]
  Output: [7,8,0,7]
  Example 2:

  Input: l1 = [2,4,3], l2 = [5,6,4]
  Output: [8,0,7]
  Example 3:

  Input: l1 = [0], l2 = [0]
  Output: [0]
 

  Constraints:

  The number of nodes in each linked list is in the range [1, 100].
  0 <= Node.val <= 9
  It is guaranteed that the list represents a number that does not have leading zeros.
 

  Follow up: Could you solve it without reversing the input lists?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// revert input lists
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // solve the problem by reverting input lists
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
        // now create the result list (MSB in head)
        int carry = 0;
        ListNode *head = nullptr;
        while(l1 || l2 || carry) {
            int val = (l1?l1->val:0) + (l2?l2->val:0) + carry;
            carry = val/10;
            ListNode *node = new ListNode(val%10);
            node->next = head;  // insert at head
            head = node;
            l1 = l1?l1->next:nullptr;
            l2 = l2?l2->next:nullptr;
        }
        
        return head;
    }
    
private:
    ListNode* reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while(cur) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};


// do not revert input lists
// but then we need to revert and propage carry in result list
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // do not revert input lists
        
        // first, we add two lists from MSB to LSB by allowing node value to go beyond 9
        // note result list is built from LSB to MSB
        int len1 = length(l1);
        int len2 = length(l2);
        ListNode *head = nullptr;
        for(int i=max(len1,len2); i>0; --i) {
            int val = (i>len1?0:l1->val) + (i>len2?0:l2->val);
            ListNode *node = new ListNode(val);
            node->next = head;  // insert at head
            head = node;
            l1 = i>len1?l1:l1->next;
            l2 = i>len2?l2:l2->next;
        }
        
        // now, we propage carry, and in the meantime we'll revert the result list
        int carry = 0;
        ListNode *prev = nullptr;
        ListNode *cur = head;  // acutal head of result list
        while(cur) {
            int val = cur->val + carry;
            cur->val = val%10;
            carry = val/10;
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        if(carry) {
            ListNode *node = new ListNode(carry);
            node->next = prev;
            prev = node;
        }
        
        return prev;
    }
    
private:
    int length(ListNode *head) {
        int len = 0;
        while(head) {
            ++len;
            head = head->next;
        }
        return len;
    }
    
};


// use stack to revert input lists -- looks like cheating...
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1;
        stack<int> s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }    
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }    
        ListNode* head = nullptr;
        int sum = 0;
        while (!s1.empty() || !s2.empty() || sum) {
            sum += s1.empty() ? 0 : s1.top();
            sum += s2.empty() ? 0 : s2.top();
            if (!s1.empty()) s1.pop();
            if (!s2.empty()) s2.pop();            
            ListNode* n = new ListNode(sum % 10);
            sum /= 10;
            n->next = head;
            head = n;      
        }    
        return head;      
    }
};
