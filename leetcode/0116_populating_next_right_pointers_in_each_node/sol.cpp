#include "../common/common.h"

using namespace std;

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

// This is true O(1) space solution
class Solution{
public:
  void connect(TreeLinkNode *root) {
    TreeLinkNode *pStart = root;
    while(pStart) {  // current level is not empty
      TreeLinkNode *pCur = pStart;
      // build links for next level from current level
      while(pCur) {
	if(pCur->left)
	  pCur->left->next = pCur->right;
	if(pCur->right && pCur->next)
	  pCur->right->next = pCur->next->left;
	pCur = pCur->next;
      }
      pStart = pStart->left;
    }
  }
};


// This is strictly O(1) space solution due to the call-stack for recursion
class Solution2{
public:
  void connect(TreeLinkNode *root) {
    if(!root)
      return;

    // assume perfect binary-tree
    if(root->left && root->right) {
      root->left->next = root->right;
      root->right->next = root->next ? root->next->left : nullptr;
      connect(root->left);
      connect(root->right);
    }    
  }
};
