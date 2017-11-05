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

// A better solution w/o extra visited node cache
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode *pCur = root;
    while(pCur || !s.empty()) {
      if(pCur) {
	s.push(pCur);
	pCur = pCur->left;
      }
      else {  
	pCur = s.top();  // upon here, the left tree of pCur has already been processed
	s.pop();
	res.push_back(pCur->val);
	pCur = pCur->right;
      }
    }

    return res;
  }

};

class Solution2 {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    if(!root)
      return res;

    set<TreeNode*> visited;
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()) {
      TreeNode *node = stk.top();
      if(node->left && visited.find(node->left)==visited.end()) {
	stk.push(node->left);
	continue;
      }

      res.push_back(node->val);
      stk.pop();
      visited.insert(node);
      
      if(node->right && visited.find(node->right)==visited.end())
	stk.push(node->right);
    }

    return res;
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc, argv);
  Solution sol;
  auto res = sol.inorderTraversal(root);
  printVector(res);

  return 0;
}
