/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

 

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
 

Follow up: Could you solve it both recursively and iteratively?
*/

// Recursive approach
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
    bool isSymmetric(TreeNode* root) {
        if(!root)
            return false;
        return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode *root1, TreeNode *root2) {
        if(!root1 && !root2)
            return true;
        if(!root1 || !root2)
            return false;
        
        return root1->val==root2->val && isSymmetric(root1->left,root2->right) && isSymmetric(root1->right,root2->left);
    }
};


// Iterative
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // iterative approach
        // two BFS, one from left to right, and another from right to left
        // if the tree is symmetric, then the two BFS result should be same
        queue<TreeNode*> ql;  // left-->right
        queue<TreeNode*> qr;  // right-->left
        ql.push(root);
        qr.push(root);
        while(ql.size() || qr.size()) {
            TreeNode *nl = ql.front();
            ql.pop();
            TreeNode *nr = qr.front();
            qr.pop();
            if(!nl && !nr)
                continue;
            if(!nl || !nr)
                return false;
            if(nl->val != nr->val)
                return false;
            ql.push(nl->left);
            ql.push(nl->right);
            qr.push(nr->right);
            qr.push(nr->left);
        }
        
        return true;
    }
};

// Iterative approach reference (in Java)
public boolean isSymmetric(TreeNode root) {
    Queue<TreeNode> q = new LinkedList<>();
    q.add(root);
    q.add(root);
    while (!q.isEmpty()) {
        TreeNode t1 = q.poll();
        TreeNode t2 = q.poll();
        if (t1 == null && t2 == null) continue;
        if (t1 == null || t2 == null) return false;
        if (t1.val != t2.val) return false;
        q.add(t1.left);
        q.add(t2.right);
        q.add(t1.right);
        q.add(t2.left);
    }
    return true;
}
