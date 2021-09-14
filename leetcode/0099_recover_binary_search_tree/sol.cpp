/*
You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

 

Example 1:


Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
Example 2:


Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 

Constraints:

The number of nodes in the tree is in the range [2, 1000].
-2^31 <= Node.val <= 2^31 - 1
 

Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// recursive approach
// O(N) time complexity, O(h) space complexity
class Solution {
public:
    void recoverTree(TreeNode* root) {
        // think about the problem of recovering a sorted array (inorder traversal)
        // -- first elem is the one that starts to decrease
        // -- second elem is the one with lowest val after the first elem, or in another form, the one that drops for the first or second time
        inorder(root);
        int val = _node1->val;
        _node1->val = _node2->val;
        _node2->val = val;
    }
    
private:
    TreeNode *_prev = nullptr;
    TreeNode *_node1 = nullptr;
    TreeNode *_node2 = nullptr;
    void inorder(TreeNode *node) {
        if(node->left)
            inorder(node->left);
        
        if(_prev && node->val<_prev->val) {
            _node2 = node;
            if(!_node1)
                _node1 = _prev;
            else
                return;  // second drop found, we've found both nodes -- early exit
        }
        _prev = node;
        
        if(node->right)
            inorder(node->right);
    }
};


// a slightly different impl
class Solution {
public:
    void recoverTree(TreeNode* root) {
        // think about the problem of recovering a sorted array (inorder traversal)
        // -- first elem is the one that starts to decrease
        // -- second elem is the one with lowest val after the first elem
        inorder(root);
        int val = _node1->val;
        _node1->val = _node2->val;
        _node2->val = val;
    }
    
private:
    TreeNode *_prev = nullptr;
    TreeNode *_node1 = nullptr;
    TreeNode *_node2 = nullptr;
    void inorder(TreeNode *node) {
        if(node->left)
            inorder(node->left);
        
        if(_prev && node->val<_prev->val) {
            if(!_node1)
                _node1 = _prev;
            _node2 = node;
        }
        _prev = node;
        
        if(node->right)
            inorder(node->right);
    }
};


// reference using Morris traversal (in Jav)
// O(1) space
class Solution {
  public void swap(TreeNode a, TreeNode b) {
    int tmp = a.val;
    a.val = b.val;
    b.val = tmp;
  }

  public void recoverTree(TreeNode root) {
    // predecessor is a Morris predecessor. 
    // In the 'loop' cases it could be equal to the node itself predecessor == root.
    // pred is a 'true' predecessor, 
    // the previous node in the inorder traversal.
    TreeNode x = null, y = null, pred = null, predecessor = null;

    while (root != null) {
      // If there is a left child
      // then compute the predecessor.
      // If there is no link predecessor.right = root --> set it.
      // If there is a link predecessor.right = root --> break it.
      if (root.left != null) {
        // Predecessor node is one step left 
        // and then right till you can.
        predecessor = root.left;
        while (predecessor.right != null && predecessor.right != root)
          predecessor = predecessor.right;

        // set link predecessor.right = root
        // and go to explore left subtree
        if (predecessor.right == null) {
          predecessor.right = root;
          root = root.left;
        }
        // break link predecessor.right = root
        // link is broken : time to change subtree and go right
        else {
          // check for the swapped nodes
          if (pred != null && root.val < pred.val) {
            y = root;
            if (x == null) x = pred;
          }
          pred = root;

          predecessor.right = null;
          root = root.right;
        }
      }
      // If there is no left child
      // then just go right.
      else {
        // check for the swapped nodes
        if (pred != null && root.val < pred.val) {
          y = root;
          if (x == null) x = pred;
        }
        pred = root;

        root = root.right;
      }
    }
    swap(x, y);
  }
};
