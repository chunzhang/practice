/*
Facebook/Google/Adobe

Given the root of a binary tree, determine if it is a complete binary tree.

In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
Example 2:


Input: root = [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.
 

Constraints:

The number of nodes in the tree is in the range [1, 100].
1 <= Node.val <= 1000
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

// BFS: for a complete binary tree, there is no gap (i.e., null child) during BFS
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        bool seenNull = false;  // whether has encountered null node so far
        while(q.size()) {
            TreeNode *cur = q.front();
            q.pop();
            if(!cur) {
                seenNull = true;
            }
            else {
                if(seenNull)
                    return false;
                q.push(cur->left);
                q.push(cur->right);
            }
        }

        return true;
    }
};

// DFS
// same idea as array representation of a binary tree (i.e., the one used in leetcode)
// -- for node with id, it's left and right child is stored at 2*id+1 and 2*id+2 respectively
// -- for a complete binary tree, the ID ranges from 0 to totalNumNodes-1
// as such, we can do a DFS and check node's ID; if any ID is out of the range, the tree is incomplete
class Solution {
    bool isCompleteTree(TreeNode* root) {
        // cannot use auto here, or otherwise complier does not recognize the recursive lambda function call
        function<int(const TreeNode*)> countNodes = [&](const TreeNode *node) {
            if(!node)
                return 0;
            return countNodes(node->left)+countNodes(node->right)+1;
        };
        const int numNodes = countNodes(root);

        function<bool(const TreeNode*,const int id, const int numNodes)> dfs = 
        [&](const TreeNode *node, const int id, const int numNodes) {
            if(!node)
                return true;
            if(id >= numNodes)
                return false;
            return dfs(node->left,2*id+1,numNodes) && dfs(node->right,2*id+2,numNodes);
        };
        return dfs(root,0,numNodes);
    }
};
