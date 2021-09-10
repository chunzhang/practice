/*
Given the root of a binary search tree and the lowest and highest boundaries as low and high, trim the tree so that all its elements lies in [low, high]. Trimming the tree should not change the relative structure of the elements that will remain in the tree (i.e., any node's descendant should remain a descendant). It can be proven that there is a unique answer.

Return the root of the trimmed binary search tree. Note that the root may change depending on the given bounds.

 

Example 1:


Input: root = [1,0,2], low = 1, high = 2
Output: [1,null,2]
Example 2:


Input: root = [3,0,4,null,2,null,null,1], low = 1, high = 3
Output: [3,2,null,1]
Example 3:

Input: root = [1], low = 1, high = 2
Output: [1]
Example 4:

Input: root = [1,null,2], low = 1, high = 3
Output: [1,null,2]
Example 5:

Input: root = [1,null,2], low = 2, high = 4
Output: [2]
 

Constraints:

The number of nodes in the tree in the range [1, 10^4].
0 <= Node.val <= 10^4
The value of each node in the tree is unique.
root is guaranteed to be a valid binary search tree.
0 <= low <= high <= 10^4
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

// DFS
// since the input is BST, when a node needs to be trimmed, either it's left or right sub-tree needs to be trimmed
// -- this guarantess non-ambiguity of the solution
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root->left)
            root->left = trimBST(root->left, low, high);
        if(root->right)
            root->right = trimBST(root->right, low, high);
        
        if(root->val < low) {
            TreeNode *newRoot = root->right;
            //delete root;
            return newRoot;
        }
        else if(root->val > high) {
            TreeNode *newRoot = root->left;
            //delete root;
            return newRoot;
        }
        else {
            return root;
        }
    }
};


// a more concise impl, but it cannot free memory of trimmed nodes
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(!root)  // important as we may pass nullptr in the recursive call
            return nullptr;
        if(root->val < low)
            return trimBST(root->right, low, high);
        else if(root->val > high)
            return trimBST(root->left, low, high);
        
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};
