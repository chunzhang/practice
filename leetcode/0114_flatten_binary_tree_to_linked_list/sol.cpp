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

// This is an iterative approach -- idea is to re-connect tail of left-subtree to head of right-subtree one at a time in a top-down manner
class Solution {
public:
  void flatten(TreeNode* root) {
    TreeNode *pCur = root;
    while(pCur) {
      if(pCur->left) {
	TreeNode *pTail = pCur->left;
	while(pTail->right)
	  pTail = pTail->right;
	// reconnect
	pTail->right = pCur->right;
	pCur->right = pCur->left;
	pCur->left = nullptr;
      }
      pCur = pCur->right;
    }
  }

};

class Solution2 {
public:
  void flatten(TreeNode* root) {
    flat(root);
  }

  // return tail
  TreeNode* flat(TreeNode *root) {
    if(!root)
      return nullptr;

    TreeNode *left = root->left;
    TreeNode *right = root->right;
    TreeNode *tail = root;

    if(left) {
      root->left = nullptr;
      root->right = left;
      tail = flat(left);
    }

    if(right) {
      tail->right = right;
      tail = flat(right);
    }

    return tail;
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  sol.flatten(root);
  printTree(root);

  return 0;
}
