/*
  Given a binary tree, find the length of the longest consecutive sequence path.

  The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

  For example,
  1
   \
    3
   / \
  2   4
       \
        5
 Longest consecutive sequence path is 3-4-5, so return 3.
    2
     \
      3
     / 
    2    
   / 
  1
  Longest consecutive sequence path is 2-3,not3-2-1, so return 2
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  int longestConsecutive(TreeNode* root) {
    int maxLen = 0;
    if(root)
      search(root, maxLen);
    return maxLen;
  }

  // return length of longest consecutive sequence that starts from "root"
  int search(TreeNode *root, int &maxLen) {
    int len = 1;
    if(root->left) {
      int lenLeft = search(root->left, maxLen);
      if(root->left->val == root->val+1)
	len = 1 + lenLeft;
    }
    if(root->right) {
      int lenRight = search(root->right, maxLen);
      if(root->right->val == root->val+1)
	len = max(len, 1+lenRight);
    }

    maxLen = max(maxLen, len);
    return len;
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  int maxLen = sol.longestConsecutive(root);
  cout << "maxLen : " << maxLen << endl;

  return 0;
}
