/*
Given a Circular Linked List node, which is sorted in non-descending order, write a function to insert a value insertVal into the list such that it remains a sorted circular list. The given node can be a reference to any single node in the list and may not necessarily be the smallest value in the circular list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the circular list should remain sorted.

If the list is empty (i.e., the given node is null), you should create a new single circular list and return the reference to that single node. Otherwise, you should return the originally given node.

 

Example 1:


 
Input: head = [3,4,1], insertVal = 2
Output: [3,4,1,2]
Explanation: In the figure above, there is a sorted circular list of three elements. You are given a reference to the node with value 3, and we need to insert 2 into the list. The new node should be inserted between node 1 and node 3. After the insertion, the list should look like this, and we should still return node 3.



Example 2:

Input: head = [], insertVal = 1
Output: [1]
Explanation: The list is empty (given head is null). We create a new single circular list and return the reference to that single node.
Example 3:

Input: head = [1], insertVal = 0
Output: [1,0]
 

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-106 <= Node.val, insertVal <= 106
*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/


class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *node = new Node(insertVal);

        if(!head) {
            node->next = node;
            return node;
        }

        // 1) if we can find two nodes where curNodeVal <= insertVal <= nextNodeVal, this is the location to insert the new node
        // 2) otherwise, the new node needs to be inserted after the last maxNode (because insertVal is either min or max in the new linked list)
        int maxVal = INT_MIN;
        Node *maxNode = nullptr;
        Node *cur = head;
        do {
            // case 1): insert between the two nodes
            if(cur->val<=insertVal && insertVal<=cur->next->val) {
                node->next = cur->next;
                cur->next = node;
                break;
            }

            // to keep track of last node with maxVal
            if(cur->val >= maxVal) {
                maxVal = cur->val;
                maxNode = cur;
            }
            cur = cur->next;
        } while(cur!=head);

        // case 2)
        if(!node->next) {
            node->next = maxNode->next;
            maxNode->next = node;
        }
        
        return head;
    }
};


// reference solution (Java)
class Solution {
  public Node insert(Node head, int insertVal) {
    if (head == null) {
      Node newNode = new Node(insertVal, null);
      newNode.next = newNode;
      return newNode;
    }

    Node prev = head;
    Node curr = head.next;
    boolean toInsert = false;

    do {
      if (prev.val <= insertVal && insertVal <= curr.val) {
        // Case 1).
        toInsert = true;
      } else if (prev.val > curr.val) {  // prev is the max and curr is the min of the existing linked list
        // Case 2).
        if (insertVal >= prev.val || insertVal <= curr.val)
          toInsert = true;
      }

      if (toInsert) {
        prev.next = new Node(insertVal, curr);
        return head;
      }

      prev = curr;
      curr = curr.next;
    } while (prev != head);

    // Case 3).
    prev.next = new Node(insertVal, curr);
    return head;
  }
}
