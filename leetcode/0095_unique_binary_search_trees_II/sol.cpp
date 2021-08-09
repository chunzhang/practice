/*
Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

 

Example 1:


Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
Example 2:

Input: n = 1
Output: [[1]]
 

Constraints:

1 <= n <= 8
*/


// Recursively build all trees
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
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return buildTreeRec(1, n);
    }

    // TODO: can add destructor
    
private:
    vector<TreeNode*> buildTreeRec(int s, int e) {
        vector<TreeNode*> res;
        
        if(s > e) {
            res.push_back(nullptr);
        }
        else if(s == e) {
            res.push_back(new TreeNode(s));
        }
        else {
            for(int k=s; k<=e; ++k)  // all possible roots
                for(TreeNode *left : buildTreeRec(s, k-1))
                    for(TreeNode *right : buildTreeRec(k+1,e)) {
                        TreeNode *root = new TreeNode(k, left, right);
                        res.push_back(root);
                    }
        }
        
        return res;
    }
};


// Bottom-up build
class Solution {
public:
    // This is the DP approach
    vector<TreeNode*> generateTrees(int n) {
        if(n < 1)
            return vector<TreeNode*>();
        
        vector<vector<TreeNode*> > trees(n+1, vector<TreeNode*>());
        trees[0].push_back(NULL);
        
        for(int i=1; i<=n; ++i) {
            for(int j=0; j<i; ++j) {
                vector<TreeNode*> leftTrees = trees[j];
                vector<TreeNode*> rightTrees = trees[i-j-1];
                for(TreeNode *lt : leftTrees) {
                    for(TreeNode *rt : rightTrees) {
                        TreeNode *root = new TreeNode(j+1);
                        root->left = lt;
                        root->right = cloneTree(rt, /*to minus this offset*/j+1);
                        trees[i].push_back(root);
                    }
                }
            }
        }
        
        return trees[n];
    }

private:
    TreeNode* cloneTree(TreeNode *root, int offset) {
        if(!root)
            return NULL;
        TreeNode *newRoot = new TreeNode(root->val + offset);
        newRoot->left = cloneTree(root->left, offset);
        newRoot->right = cloneTree(root->right, offset);
        return newRoot;
    }
    
};
