/*
A binary tree is uni-valued if every node in the tree has the same value.

Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.

 

Example 1:


Input: root = [1,1,1,1,1,null,1]
Output: true
Example 2:


Input: root = [2,2,2,5,2]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 100].
0 <= Node.val < 100
*/

// DFS impl 1
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        bool lu = true;
        bool ru = true;
        if(root->left) {
            lu = root->left->val==root->val && isUnivalTree(root->left);
        }
        if(root->right) {
            ru = root->right->val==root->val && isUnivalTree(root->right);
        }
        
        return lu&&ru;
    }
};

// DFS impl 2
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        return preorder(root, root->val);
    }
    
private:
    bool preorder(TreeNode *node, int val) {
        if(node->val != val)
            return false;
        if(node->left && !preorder(node->left,val))
            return false;
        if(node->right && !preorder(node->right,val))
            return false;
        return true;
    }
};

// BFS
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        // BFS
        int val = root->val;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if(node->val != val)
                return false;
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        return true;
    }
};
