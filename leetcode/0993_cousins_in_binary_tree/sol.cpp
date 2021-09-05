/*
Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.

 

Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:


Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Constraints:

The number of nodes in the tree is in the range [2, 100].
1 <= Node.val <= 100
Each node has a unique value.
x != y
x and y are exist in the tree.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// One time of pre-order traversal, record parent and level for x and y
// o(N) time complexity
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        find(root, x, y, -1/*starting parent val*/, 0/*starting level*/);
        return _xl==_yl&&_xp!=_yp;
    }
    
private:
    int _xp;  // parent val of x and y
    int _yp;
    int _xl;  // level of x and y
    int _yl;
    
    void find(TreeNode *node, int x, int y, int parent, int level) {
        if(node->val == x) {
            _xp = parent;
            _xl = level;
        }
        if(node->val == y) {
            _yp = parent;
            _yl = level;
        }
        
        if(node->left)
            find(node->left, x, y, node->val, level+1);
        if(node->right)
            find(node->right, x, y, node->val, level+1);
    }
        
};
