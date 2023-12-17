/*
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:


Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
Example 2:

Input: root = [1,null,3]
Output: [1,3]
Example 3:

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


// BFS: level based traversal
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        // level based traversal to get right most node at each level
        vector<int> ans;
        queue<TreeNode*> q;
        if(root)
            q.push(root);

        while(!q.empty()) {
            int val = 0;
            int sz = q.size();
            while(sz--) {
                TreeNode *node = q.front();
                q.pop();
                val = node->val;
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
            ans.push_back(val);
        }

        return ans;
    }
};


// Recursion: combine right side view from right tree and left tree
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        // use recursion
        vector<int> ans;
        if(!root)
            return ans;

        ans.push_back(root->val);
        auto leftAns = rightSideView(root->left);
        auto rightAns = rightSideView(root->right);
        
        int i = 0;
        while(i < rightAns.size())
            ans.push_back(rightAns[i++]);
        while(i < leftAns.size())
            ans.push_back(leftAns[i++]);

        return ans;
    }
};
