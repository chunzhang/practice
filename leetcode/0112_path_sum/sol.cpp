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
  bool hasPathSum(TreeNode* root, int sum) {
    if(!root)  // Note empty node does not become a valid path, so it should return False
      return false;

    if(!root->left && !root->right)
      return sum==root->val;

    return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
  }

};
