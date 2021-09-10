/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the tree.

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

// For a given root, recursively call LCA(root->left, p, q) and LCA(root->right, p, q)
// -- if both returns a valid node which means p, q are in different subtrees, then root will be their LCA.
// -- if only one valid node returns, which means p, q are in the same subtree, return that valid node as their LCA.
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return nullptr;
        if(root==p || root==q)  // one of the node is found
            return root;
        
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if(left && right)  // if one node exists in left tree and another node exists in right tree, then root is the LCA
            return root;
        return left?left:right;
    }
};

// my DFS search that keeps the path
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path;
        dfs(root, p->val, q->val, path);
        TreeNode *lca = nullptr;
        for(int i=0; i<min(p1.size(),p2.size())&&p1[i]==p2[i]; ++i) {
            lca = p1[i];
        }
        
        return lca;
    }
    
private:
    vector<TreeNode*> p1;
    vector<TreeNode*> p2;
    void dfs(TreeNode *node, int v1, int v2, vector<TreeNode*> &path) {
        path.push_back(node);
        if(node->val == v1)
            p1 = path;
        else if(node->val == v2) 
            p2 = path;
        
        if(p1.size() && p2.size())  // both paths have been found, no need to search further
            return;
            
        if(node->left)
            dfs(node->left, v1, v2, path);
        if(node->right)
            dfs(node->right, v1, v2, path);
        
        path.pop_back();
    }
};
