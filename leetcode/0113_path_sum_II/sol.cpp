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
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> paths;
    vector<int> path;
    if(root)
      search(root, sum, path, paths);
    return paths;
  }

  void search(TreeNode *root, int sum, vector<int> &path, vector<vector<int>> &paths) {
    if(!root->left && !root->right && root->val==sum) {
      path.push_back(root->val);
      paths.push_back(path);
      path.pop_back();
      return;
    }

    path.push_back(root->val);
    if(root->left)
      search(root->left, sum-root->val, path, paths);
    if(root->right)
      search(root->right, sum-root->val, path, paths);
    path.pop_back();
  }
};

int main(int argc, char *argv[])
{
  TreeNode *root = makeTree(argc-1, argv);
  int sum = atoi(argv[argc-1]);
  Solution sol;
  auto paths = sol.pathSum(root, sum);
  printMatrix(paths);

  return 0;
}
