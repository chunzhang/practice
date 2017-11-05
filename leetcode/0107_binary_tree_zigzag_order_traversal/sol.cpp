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
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root)
      return res;
    vector<TreeNode*> curLevel{root};
    while(!curLevel.empty()) {
      int sz = curLevel.size();
      vector<int> level(sz, 0);
      vector<TreeNode*> nextLevel;
      for(int i=0; i<sz; ++i) {
	TreeNode *node = curLevel[i];
	int index = res.size()%2 ? sz-1-i: i;  // With this, we no longer need to reverse the level
	level[index] = node->val;
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
  auto res = sol.zigzagLevelOrder(root);
  printMatrix(res);

  return 0;
}
