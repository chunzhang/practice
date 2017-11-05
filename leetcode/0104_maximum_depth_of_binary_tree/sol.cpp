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
  Solution() : _depth(0) { }
  int maxDepth(TreeNode* root) {
    if(root)
      preorder(root, 1);
    return _depth;
  }

  void preorder(TreeNode *root, int level) {
    if(level > _depth)
      _depth = level;

    if(root->left)
      preorder(root->left, level+1);
    if(root->right)
      preorder(root->right, level+1);
  }

private:
  int _depth;
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  int depth = sol.maxDepth(root);
  cout << "depth: " << depth << endl;

  return 0;
}
