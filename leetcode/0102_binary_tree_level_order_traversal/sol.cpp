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
  vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root)
      return res;
    vector<TreeNode*> curLevel{root};
    while(!curLevel.empty()) {
      vector<int> level;
      vector<TreeNode*> nextLevel;
      for(TreeNode *node : curLevel) {
	level.push_back(node->val);
	if(node->left)
	  nextLevel.push_back(node->left);
	if(node->right)
	  nextLevel.push_back(node->right);
      }
      res.push_back(level);
      curLevel.swap(nextLevel);
    }

    return res;
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  auto res = sol.levelOrder(root);
  printMatrix(res);

  return 0;
}
