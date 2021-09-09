/*
  Given the root of a binary tree, return its maximum depth.

  A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

y 

  Example 1:


  Input: root = [3,9,20,null,null,15,7]
  Output: 3
  Example 2:

  Input: root = [1,null,2]
  Output: 2
  Example 3:

  Input: root = []
  Output: 0
  Example 4:

  Input: root = [0]
  Output: 1
 

  Constraints:

  The number of nodes in the tree is in the range [0, 10^4].
  -100 <= Node.val <= 100
*/

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

// DFS simpler code
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root)
            return 0;
        return max(maxDepth(root->left),maxDepth(root->right)) + 1;
    }
};


// DFS using helper function
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
