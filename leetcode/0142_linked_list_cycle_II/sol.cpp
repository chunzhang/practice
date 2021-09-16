/*
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
Example 2:


Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
Example 3:


Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
*/


// impl 1: fast/slow starting from same location
class Solution {
public:
    // slow/fast starts from same location
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while(slow && fast) {
            slow = slow->next;
            fast = fast->next;
            fast = fast?fast->next:nullptr;
            if(slow == fast)
                break;
        }
        
        if(!fast)  // loop does not exists
            return nullptr;
                
        // starting from slow/fast meet point, when it meets slow2, it's the loop starting point
        // see reference for mathematical proof: https://www.youtube.com/watch?v=UkKBPGt5Nok
        ListNode *slow2 = head;
        while(slow != slow2) {
            slow = slow->next;
            slow2 = slow2->next; 
        }
        
        return slow;
    }
};


// impl 2: slow/fast starting from different location
class Solution {
public:
    // slow/fast starts from different location
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head?head->next:nullptr;
        while(slow && fast) {
            if(slow == fast)  // find loop
                break;
            slow = slow->next;
            fast = fast->next;
            fast = fast?fast->next:nullptr;
        }
        
        if(!fast)  // loop does not exists
            return nullptr;
        
        // starting from slow/fast meet point, when it meets slow2, it's the loop starting point
        // see reference for mathematical proof: https://www.youtube.com/watch?v=UkKBPGt5Nok
        slow = slow->next;  // since fast starts one node after slow, we need to compensate here
        ListNode *slow2 = head;
        while(slow != slow2) {
            slow = slow->next;
            slow2 = slow2->next; 
        }
        
        return slow;
    }
};
