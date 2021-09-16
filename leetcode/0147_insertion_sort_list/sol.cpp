/*
Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.

The steps of the insertion sort algorithm:

Insertion sort iterates, consuming one input element each repetition and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list and inserts it there.
It repeats until no input elements remain.
The following is a graphical example of the insertion sort algorithm. The partially sorted list (black) initially contains only the first element in the list. One element (red) is removed from the input data and inserted in-place into the sorted list with each iteration.


 

Example 1:


Input: head = [4,2,1,3]
Output: [1,2,3,4]
Example 2:


Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
 

Constraints:

The number of nodes in the list is in the range [1, 5000].
-5000 <= Node.val <= 5000

*/

// a more elegant solution, i.e., always insert node into the (new) result list
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        // insert into a new list
        ListNode dh(0);
        ListNode *cur = head;
        while(cur) {
            ListNode *next = cur->next;
            
            // find node (from the new list) to insert after
            ListNode *node = &dh;
            while(node->next && node->next->val<cur->val)
                node = node->next;
            
            // insert after node in the new list
            cur->next = node->next;
            node->next = cur;
            
            cur = next;
        }
        
        return dh.next;
    }
};


// manipulate (i.e., re-organize) input list
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dh(INT_MIN);  // dummy head
        dh.next = head;
        
        // start from the second node
        ListNode *prev = head;
        ListNode *cur = head->next;
        while(cur) {
            // find node to insert after
            ListNode *after = &dh;
            while(after->next->val<=cur->val && after->next!=cur)
                after = after->next;
            if(after->next == cur) {  // cur should stay at current location
                cur = cur->next;
                prev = prev->next;
                continue;
            }
            
            // insert after "after node"
            ListNode *next = cur->next;
            cur->next = after->next;
            after->next = cur;
            prev->next = next;
            cur = next;
        }
        
        return dh.next;
    }
};
