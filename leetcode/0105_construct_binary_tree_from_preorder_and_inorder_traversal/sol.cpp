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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if(preorder.empty())
      return nullptr;

    return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
  }

  TreeNode* build(const vector<int> &preorder, const int prei, const int prej, const vector<int> &inorder, const int ini, const int inj) {
    int val = preorder[prei];
    TreeNode *root = new TreeNode(val);
    if(prei == prej)
      return root;
    
    int k = ini;
    for( ; k<=inj; ++k)  // find boundrary of left- and right-subtree
      if(inorder[k] == val)
	break;

    if(k-1 >= ini) {
      TreeNode *left = build(preorder, prei+1, prei+k-ini, inorder, ini, k-1);
      root->left = left;
    }

    if(k+1 <= inj) {
      TreeNode *right = build(preorder, prej-inj+k+1, prej, inorder, k+1, inj);
      root->right = right;
    }

    return root;
  }
};

int main(int argc, char *argv[])
{
  vector<int> preorder{1, 2, 4, 5, 3, 6, 7};
  vector<int> inorder{4, 2, 5, 1, 6, 3, 7};
  Solution sol;
  TreeNode *root = sol.buildTree(preorder, inorder);
  printTree(root);

  return 0;
}
