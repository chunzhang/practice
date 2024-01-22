/*
Facebook/Microsoft/LinkedIn
  
Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)". A descendant of a node x is a node y that is on the path from node x to some leaf node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.
Example 3:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
Output: null
Explanation: Node 10 does not exist in the tree, so return null.
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
 

Follow up: Can you find the LCA traversing the tree, without checking nodes existence?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// continue search even if p or q is found, and keep track of total number of p and q found
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *lca = search(root,p,q);
        return m_found==2 ? lca : nullptr;
    }

private:
    TreeNode* search(TreeNode *node, TreeNode *p, TreeNode *q) {
        if(!node)
            return nullptr;

        TreeNode *left = search(node->left,p,q);  // always search as we need to decide existence
        TreeNode *right = search(node->right,p,q);

        if(node==p || node==q) {
            ++m_found;
            return node;
        }
        else if(left && right)
            return node;
        
        return left?left:right;

    }

private:
    int m_found = 0;
};


// ref sol with same idea
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bool nodesFound = false;

        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node)
              return node;
            TreeNode* left = dfs(node->left);
            TreeNode* right = dfs(node->right);
            int conditions = 0;
            if (node == p || node == q)
              conditions++;
            if (left != NULL)
              conditions++;
            if (right != NULL)
              conditions++;
            if (conditions == 2)
              nodesFound = true;
            
            if ((left && right) || (node == p) || (node == q))
              return node;
            return left ? left : right;
        };

        TreeNode* ans = dfs(root);
        return nodesFound ? ans : NULL;
    }
};
