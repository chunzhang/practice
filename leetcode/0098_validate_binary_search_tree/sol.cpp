/*
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
*/

#include "../common/common.h"

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// solution that propagates (low, high) range
// -- when we pass numbers, need to use long
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }
    
private:
    bool isValidBST(TreeNode *node, long low, long high) {
        if(!node)
            return true;
        if(node->val<=low || node->val>=high)
            return false;
        
        bool left = isValidBST(node->left, low, node->val);
        bool right = isValidBST(node->right, node->val, high);
        return left&&right;
    }
};

// solution that propages (low,high) range
// -- pass low and high boundary TreeNode* directly, so as to be worried about integer boundary
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, nullptr, nullptr);
    }
    
private:
    bool isValidBST(TreeNode *node, TreeNode *low, TreeNode *high) {
        if(!node)
            return true;
        
        if(low&&node->val<=low->val || high&&node->val>=high->val)
            return false;
        
        bool left = isValidBST(node->left, low, node);
        bool right = isValidBST(node->right, node, high);
        return left&&right;
    }
};


// solution: in-order traversal should be strictly increasing
class Solution {
public:
  Solution() : _prev(nullptr) { }
  bool isValidBST(TreeNode* root) {
    if(!root)
      return true;

    if(!isValidBST(root->left))
      return false;

    if(_prev && root->val<_prev->val)
      return false;
    else
      _prev = root;

    if(!isValidBST(root->right))
      return false;

    return true;
  }

private:
  TreeNode *_prev;
};
