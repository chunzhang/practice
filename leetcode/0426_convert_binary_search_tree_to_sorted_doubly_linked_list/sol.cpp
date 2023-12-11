/*
  Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

  You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

  We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.

 

  Example 1:



  Input: root = [4,2,5,1,3]


  Output: [1,2,3,4,5]

  Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

  Example 2:

  Input: root = [2,1,3]
  Output: [1,2,3]
 

  Constraints:

  The number of nodes in the tree is in the range [0, 2000].
  -1000 <= Node.val <= 1000
  All the values of the tree are unique.
*/


/*
// Definition for a Node.
class Node {
public:
int val;
Node* left;
Node* right;

Node() {}

Node(int _val) {
val = _val;
left = NULL;
right = NULL;
}

Node(int _val, Node* _left, Node* _right) {
val = _val;
left = _left;
right = _right;
}
};
*/

// best solution is to remember the last and first node during in-order traversal
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root)
            return nullptr;

        inOrder(root);
        first->left = last;
        last->right = first;
        return first;
    }

    void inOrder(Node *node) {
        if(!node)
            return;

        inOrder(node->left);
        if(!last)
            first = node;
        else {
            last->right = node;
            node->left = last;
        }
        last = node;
        inOrder(node->right);
    }

private:
    Node *first = nullptr;
    Node *last = nullptr;
};


// solution 2: use recursion
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root)
            return nullptr;

        Node *newHead = root;
        Node *newTail = root;

        Node *leftHead = treeToDoublyList(root->left);
        if(leftHead) {  // break cycle in left linked list
            Node *leftTail = leftHead->left;
            leftHead->left = nullptr;
            leftTail->right = root;
            root->left = leftTail;
            newHead = leftHead;
        }

        Node *rightHead = treeToDoublyList(root->right);
        if(rightHead) {  // break cycle in right linked list
            Node *rightTail = rightHead->left;
            rightHead->left = root;
            root->right = rightHead;
            rightTail->right = nullptr;
            newTail = rightTail;
        }

        // create new cycle
        newHead->left = newTail;
        newTail->right = newHead;

        return newHead;
    }
};


// solution 1: brute-force using vector
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root)
            return nullptr;

        // brute force preOrder to collect vector of nodes in sorted order
        vector<Node*> sortedNodes;
        inOrder(sortedNodes, root);

        // construct the linked list
        for(int i=0; i<sortedNodes.size(); ++i) {
            Node *cur = sortedNodes[i];
            // successor
            cur->right = (i==sortedNodes.size()-1) ? sortedNodes.front() : sortedNodes[i+1];
            // predecessor
            cur->left = (i==0) ? sortedNodes.back() : sortedNodes[i-1];
        }

        return sortedNodes[0];
    }

    void inOrder(vector<Node*> &sortedNodes, Node *node) {
        if(node->left)
            inOrder(sortedNodes, node->left);
        sortedNodes.push_back(node);
        if(node->right)
            inOrder(sortedNodes, node->right);
    }
};
