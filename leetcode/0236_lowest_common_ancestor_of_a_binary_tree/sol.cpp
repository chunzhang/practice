/*
  Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

  According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

  _______3______
  /              \
  ___5__          ___1__
  /      \        /      \
  6      _2       0       8
  /  \
  7   4
  For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
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
class Solution {
public:
  // Assumption 1: p and q are valid nodes in the tree
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // This function resturns
    // (1) LCA if found
    // (2) p or q if either node is found through the search path
    // (3) nullptr if neither p or q is found through the search path
        
    if(!root)
      return nullptr;  // (3)
        
    if(root==p || root==q)
      return root;  // (2)
        
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if(left && right)
      return root;   // (1)
    else if(left)
      return left;   // (1)
    else if(right)
      return right;  // (1)
    else
      return nullptr;  // (3)
  }
};
