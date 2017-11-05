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
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    if(inorder.empty())
      return nullptr;

    return build(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
  }

  TreeNode* build(const vector<int> &inorder, const int ini, const int inj, const vector<int> &postorder, const int posti, const int postj) {
    int val = postorder[postj];
     TreeNode *root = new TreeNode(val);
    int k = ini;
    for( ; k<=inj; ++k)
      if(inorder[k] == val)
	break;

    int numLeft = k - ini;  // number of elements in left subtree
    if(k-1 >= ini) {
      TreeNode *left = build(inorder, ini, k-1, postorder, posti, posti+numLeft-1);
      root->left = left;
    }

    if(k+1 <= inj) {
      TreeNode *right = build(inorder, k+1, inj, postorder, posti+numLeft, postj-1);
      root->right = right;
    }

    return root;
  }
};

int main(int argc, char *argv[])
{
  vector<int> inorder{4, 2, 5, 1, 6, 3, 7};
  vector<int> postorder{4, 5, 2, 6, 7, 3, 1};
  //vector<int> inorder{2, 1, 3};
  // vector<int> postorder{2, 3, 1};
  Solution sol;
  TreeNode *root = sol.buildTree(inorder, postorder);
  printTree(root);

  return 0;
}
