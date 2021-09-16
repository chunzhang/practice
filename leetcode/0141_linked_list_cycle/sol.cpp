/*
Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
Example 2:


Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
Example 3:


Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
*/

// slow/fast pointers: starting from different postion
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *n1 = head;
        ListNode *n2 = n1?n1->next:nullptr;
        while(n1 && n2) {
            if(n1 == n2)
                return true;
            n1 = n1->next;
            n2 = n2->next;
            n2 = n2?n2->next:n2;
        }
        
        return false;
    }
};

// slow/fast pointers: starting from same postion
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while(slow && fast) {
            slow = slow->next;
            fast = fast->next;
            fast = fast?fast->next:nullptr;
            if(slow == fast)
                break;
        }

        return fast?true:false;
    }
};
