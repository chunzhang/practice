/*
Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Example 2:


Input: root = [3,9,8,4,0,1,7]
Output: [[4],[9],[3,0,1],[8],[7]]
Example 3:


Input: root = [3,9,8,4,0,1,7,null,null,null,2,5]
Output: [[4],[9,5],[3,0,1],[8,2],[7]]
Example 4:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
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

// BFS
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if(!root)
            return {};
        unordered_map<int,vector<int>> cols;  // cols-->node values mapping
        int minCol = 0;
        int maxCol = 0;
        
        // BFS, as it keeps level order implicitly
        queue<pair<TreeNode*,int>> q;
        q.push({root,0});
        while(!q.empty()) {
            TreeNode *node = q.front().first;
            int c = q.front().second;
            q.pop();
            cols[c].push_back(node->val);
            minCol = min(minCol, c);
            maxCol = max(maxCol, c);
            if(node->left)
                q.push({node->left, c-1});
            if(node->right)
                q.push({node->right, c+1});
        }
        
        // construct results
        vector<vector<int>> ans;
        for(int c=minCol; c<=maxCol; ++c) {
            auto it = cols.find(c);
            if(it != cols.end()) {
                ans.push_back(it->second);
            }
        }
        
        return ans;
    }
};
