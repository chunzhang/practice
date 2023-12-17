/*
  A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

  Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

  For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

  Return the head of the copied linked list.

  The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

  val: an integer representing Node.val
  random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
  Your code will only be given the head of the original linked list.

 

  Example 1:


  Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
  Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
  Example 2:


  Input: head = [[1,1],[2,1]]
  Output: [[1,1],[2,1]]
  Example 3:



  Input: head = [[3,null],[3,0],[3,null]]
  Output: [[3,null],[3,0],[3,null]]
  Example 4:

  Input: head = []
  Output: []
  Explanation: The given linked list is empty (null pointer), so return null.
 

  Constraints:

  0 <= n <= 1000
  -10000 <= Node.val <= 10000
  Node.random is null or is pointing to some node in the linked list.
*/

/*
// Definition for a Node.
class Node {
public:
int val;
Node* next;
Node* random;
    
Node(int _val) {
val = _val;
next = NULL;
random = NULL;
}
};
*/


// DFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // DFS
        if(!head)
            return nullptr;
        auto it = _nodes.find(head);
        if(it != _nodes.end())
            return it->second;
        
        Node *cloneHead = new Node(head->val);
        _nodes[head] = cloneHead;
        cloneHead->next = copyRandomList(head->next);
        cloneHead->random = copyRandomList(head->random);
        return cloneHead;
    }
    
private:
    unordered_map<Node*,Node*> _nodes;  // mapping to cloned nodes; also used as visitied flag
};


// clean code by iterating the linked list from first to last
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*,Node*> nodeMap;   // old --> new node mapping
        
        // iterate through old linked list (BFS)
        Node *node = head;
        while(node) {
            Node *newNode = findOrCreateNode(nodeMap, node);
            newNode->next = findOrCreateNode(nodeMap, node->next);
            newNode->random = findOrCreateNode(nodeMap, node->random);
            node = node->next;
        }

        return findOrCreateNode(nodeMap, head);
    }

private:
    Node* findOrCreateNode(unordered_map<Node*,Node*> &nodeMap, Node *node) {
        if(!node)
            return nullptr;

        auto it = nodeMap.find(node);
        if(it != nodeMap.end())
            return it->second;

        Node *newNode = new Node(node->val);
        nodeMap[node] = newNode;

        return newNode;
    }
};


// BFS w/o using queue
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head)
            return nullptr;

        // BFS w/o using queue
        Node *ans = new Node(head->val);
        _nodes[head] = ans; 
        while(head) {
            Node *cloneHead = _nodes[head];
            
            if(head->random) {
                auto it = _nodes.find(head->random);
                if(it == _nodes.end())
                    it = _nodes.emplace(head->random, new Node(head->random->val)).first;
                cloneHead->random = it->second;;
            }
            
            if(head->next) {
                auto it = _nodes.find(head->next);
                if(it == _nodes.end())
                    it = _nodes.emplace(head->next, new Node(head->next->val)).first;
                cloneHead->next = it->second;
            }
            
            head = head->next;
        }
        
        return ans;
    }
    
private:
    unordered_map<Node*,Node*> _nodes;
};


// BFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    Node* copyRandomList(Node* head) {
        _nodes[nullptr] = nullptr;
        
        // BFS
        queue<Node*> q;
        if(head) {
            q.push(head);
            _nodes[head] = new Node(head->val);
        }
        while(q.size()) {
            Node *n = q.front();
            q.pop();
            
            Node *next = n->next;
            if(_nodes.find(next) == _nodes.end()) {
                q.push(next);
                _nodes[next] = new Node(next->val);
            }
            _nodes[n]->next = _nodes[next];
            
            Node *random = n->random;
            if(_nodes.find(random) == _nodes.end()) {
                q.push(random);
                _nodes[random] = new Node(random->val);
            }
            _nodes[n]->random = _nodes[random];
        }
        
        return _nodes[head];
    }
    
private:
    unordered_map<Node*,Node*> _nodes;
};


// reference impl with O(1) space (in Java)
// 
 public class Solution {
  public Node copyRandomList(Node head) {

      if (head == null) {
          return null;
      }

      // Creating a new weaved list of original and copied nodes.
      Node ptr = head;
      while (ptr != null) {

          // Cloned node
          Node newNode = new Node(ptr.val);

          // Inserting the cloned node just next to the original node.
          // If A->B->C is the original linked list,
          // Linked list after weaving cloned nodes would be A->A'->B->B'->C->C'
          newNode.next = ptr.next;
          ptr.next = newNode;
          ptr = newNode.next;
      }

      ptr = head;

      // Now link the random pointers of the new nodes created.
      // Iterate the newly created list and use the original nodes' random pointers,
      // to assign references to random pointers for cloned nodes.
      while (ptr != null) {
          ptr.next.random = (ptr.random != null) ? ptr.random.next : null;
          ptr = ptr.next.next;
      }

      // Unweave the linked list to get back the original linked list and the cloned list.
      // i.e. A->A'->B->B'->C->C' would be broken to A->B->C and A'->B'->C'
      Node ptr_old_list = head; // A->B->C
      Node ptr_new_list = head.next; // A'->B'->C'
      Node head_old = head.next;
      while (ptr_old_list != null) {
          ptr_old_list.next = ptr_old_list.next.next;
          ptr_new_list.next = (ptr_new_list.next != null) ? ptr_new_list.next.next : null;
          ptr_old_list = ptr_old_list.next;
          ptr_new_list = ptr_new_list.next;
      }
      return head_old;
  }
 }
