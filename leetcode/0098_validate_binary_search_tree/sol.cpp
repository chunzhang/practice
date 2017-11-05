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
