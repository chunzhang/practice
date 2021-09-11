/*
Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.

The length of the path between two nodes is represented by the number of edges between them.

 

Example 1:


Input: root = [5,4,5,1,1,5]
Output: 2
Example 2:


Input: root = [1,4,5,4,4,5]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000
The depth of the tree will not exceed 1000.
*/

// O(N) algorithm
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        _max = 0;
        longestDownPath(root);
        return _max;
    }
    
private:
    int _max;
    // return number of nodes of longest univalue path from node and downwards
    // also update global max univalue path
    int longestDownPath(TreeNode *node) {
        if(!node)
            return 0;
        
        int l = longestDownPath(node->left);
        int r = longestDownPath(node->right);
        if(!node->left || node->left->val!=node->val)
            l = 0;
        if(!node->right || node->right->val!=node->val)
            r = 0;
        
        _max = max(_max, l+r);  // path-length = #nodes - 1
        return max(l,r)+1;
    }
};
