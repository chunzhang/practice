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
class Solution {
public:
  void connect(TreeLinkNode *root) {
    TreeLinkNode *pStart = root;
    while(pStart) {  // if current level is not empty
      TreeLinkNode *pCur = pStart;
      TreeLinkNode *pStartNext = nullptr;  // first node in next level
      TreeLinkNode *pTailNext = nullptr;   // tail node in next level
      while(pCur) {
	if(pCur->left) {
	  if(!pStartNext) {
	    pStartNext = pTailNext = pCur->left;
	  }
	  else {
	    pTailNext->next = pCur->left;
	    pTailNext = pCur->left;
	  }
	}
	if(pCur->right) {
	  if(!pStartNext) {
	    pStartNext = pTailNext = pCur->right;
	  }
	  else {
	    pTailNext->next = pCur->right;
	    pTailNext = pCur->right;
	  }
	}
	pCur = pCur->next;
      }
      pStart = pStartNext;
    }
  }
};
