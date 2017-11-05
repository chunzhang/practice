#include "../common/common.h"
#include <stack>

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
  vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    if(!root)
      return res;
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()) {
      TreeNode *pCur = s.top();
      s.pop();
      res.push_back(pCur->val);
      if(pCur->right)
	s.push(pCur->right);
      if(pCur->left)
	s.push(pCur->left);
    }

    return res;
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  auto res = sol.preorderTraversal(root);
  printVector(res);

  return 0;
}
