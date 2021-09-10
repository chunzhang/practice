/*
Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.

 

Example 1:


Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]
Example 2:

Input: root = [1]
Output: ["1"]
 

Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100
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
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        string path;
        if(root)
            dfs(root, path, ans);
        return ans;
    }
    
private:
    void dfs(TreeNode *node, string &path, vector<string> &ans) {
        int oldLen = path.size();
        path += (path.empty()?"":"->") + to_string(node->val);
        if(!node->left && !node->right)
            ans.push_back(path);
        
        if(node->left)
            dfs(node->left, path, ans);
        if(node->right)
            dfs(node->right, path, ans);
        
        path.resize(oldLen);  // need to recover path string
    }
};
