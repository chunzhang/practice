/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: 2
Example 2:

Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5
 

Constraints:

The number of nodes in the tree is in the range [0, 10^5].
-1000 <= Node.val <= 1000
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

// DFS impl 1
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        if(!root->left && !root->right)
            return 1;
        if(!root->left)
            return minDepth(root->right) + 1;
        if(!root->right)
            return minDepth(root->left) + 1;
        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

// DFS impl 2
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        if(l && r)  // note empty branch does not contribute to depth of a tree
            return min(l,r)+1;
        else if(l)
            return l+1;
        else if(r)
            return r+1;
        else
            return 1;
    }
};


// BFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        
        // BFS
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        while(!q.empty()) {
            ++level;
            int sz = q.size();
            while(sz--) {
                TreeNode *node = q.front();
                q.pop();
                if(!node->left && !node->right)  // found first leaf, we can return as it has min-depth in BFS
                    return level;
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
        }
        
        return 0;  // only reaches here when root is nullptr
    }
};
