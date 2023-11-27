/*
Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).

Each node will have a reference to its parent node. The definition for Node is below:

class Node {
    public int val;
    public Node left;
    public Node right;
    public Node parent;
}
According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)."

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5 since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q exist in the tree.
*/

// recursive check parent-child relationship
class Solution {
public:
    bool isParent(Node* p, Node* q){
        if(p == q) return true;
        if(p == NULL) return false;

        return isParent(p->right,q) || isParent(p->left,q);

    }
    Node* lowestCommonAncestor(Node* p, Node * q) {
        if(isParent(p,q)) return p;
        if(isParent(q,p)) return q;

        if(p != NULL) p = p->parent;
        if(q != NULL) q = q->parent;
        return lowestCommonAncestor(p,q);
    }
};


// hash one path
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        // store all nodes from p-->root in a hash-table
        // then, when traversing q-->root, the firt node found in the has is the LCA
        unordered_set<Node*> pPath;
        while(p) {
            pPath.insert(p);
            p = p->parent;
        }
        while(q) {
            if(pPath.count(q))  // find LCA
                return q;
            q = q->parent;
        }

        return nullptr;  // should not reach here
    }
};

// calculate both paths
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        // compute full path from root-->p and root-->q
        stack<Node*> pPath;
        stack<Node*> qPath;
        Node *node = p;
        while(node) {
            pPath.push(node);
            node = node->parent;
        }
        node = q;
        while(node) {
            qPath.push(node);
            node = node->parent;
        }

        Node *lca = nullptr;
        while(!pPath.empty() && !qPath.empty() && pPath.top()==qPath.top()) {
            lca = pPath.top();
            pPath.pop();
            qPath.pop();
        }
        return lca;
    }
};
