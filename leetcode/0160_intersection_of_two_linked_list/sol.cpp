/*
  Write a program to find the node at which the intersection of two singly linked lists begins.


  For example, the following two linked lists:

  A:          a1 → a2
  ↘
  c1 → c2 → c3
  ↗            
  B:     b1 → b2 → b3
  begin to intersect at node c1.


  Notes:

  If the two linked lists have no intersection at all, return null.
  The linked lists must retain their original structure after the function returns.
  You may assume there are no cycles anywhere in the entire linked structure.
  Your code should preferably run in O(n) time and use only O(1) memory.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Compute length delta to decide starting point
class Solution {
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int len1 = length(headA);
    int len2 = length(headB);
    if(len1 > len2)
      headA = forward(headA, len1-len2);
    else if(len1 < len2)
      headB = forward(headB, len2-len1);
    while(headA && headB && headA!=headB) {
      headA = headA->next;
      headB = headB->next;
    }
        
    return headA==headB ? headA : nullptr;
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
    
  ListNode* forward(ListNode *head, int n) {
    while(n--) {
      head = head->next;
    }
    return head;
  }
};

// This is essentially the same idea of utilizing length delta to get correct starting
// position, however the implementation is much more concise
class Solution {
public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    // Assume listA has length 7, listB has length 5, and the merged list has length 3
    // -- i.e., A=[1,2,3,4,5,6,7], B=[8,9,5,6,7], and they merge on 5
    // -- pB would be redirected to headA first because B has shorter length
    // -- pA would be redirected to headB after the new pB has made another two moves, which
    //    is essentially the delta of length between A and B!
    // -- After that, pA and pB would move until a common node is reached!
    ListNode *pA = headA;
    ListNode *pB = headB;
    while(pA != pB) {
      pA = pA ? pA->next : headB;
      pB = pB ? pB->next : headA;
    }
        
    return pA;
  }
};
