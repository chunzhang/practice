/*
Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.

It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.

A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.

A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.

 

Example 1:


Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]
Example 2:

Input: preorder = [1,3]
Output: [1,null,3]
 

Constraints:

1 <= preorder.length <= 100
1 <= preorder[i] <= 108
All the values of preorder are unique.
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

// BST ==> 1) node values are unique; 2) node values are sorted
// worst case O(N^2) time complexity, if preorder is [7,6,5,4,...]
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return buildRange(preorder, 0, preorder.size());
    }
    
private:
    // build BST from [i,j) range of preorder traversal
    TreeNode *buildRange(const vector<int> &preorder, int i, int j) {
        if(i >= j)
            return nullptr;
        
        TreeNode *root = new TreeNode(preorder[i]);
        int jj = i + 1;
        while(jj<preorder.size() && preorder[jj]<preorder[i])  // jj points to first element greater than root val
            ++jj;
        
        root->left = buildRange(preorder, i+1,jj);
        root->right = buildRange(preorder, jj, j);

        return root;
    }
};


// use binary search to find boundary cut
// O(NlgN) time complexity
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return buildRange(preorder, preorder.begin(), preorder.end());
    }
    
private:
    // build BST from [it,jt) range of preorder traversal
    // using iterator makes life easier
    TreeNode *buildRange(const vector<int> &preorder, vector<int>::iterator it, vector<int>::iterator jt) {
        if(it == jt)
            return nullptr;
        
        TreeNode *root = new TreeNode(*it);
        vector<int>::iterator kt = upper_bound(it, jt, *it);  // binary search, i.e., kt to first element greater than root val
        
        root->left = buildRange(preorder, ++it,kt);
        root->right = buildRange(preorder, kt, jt);

        return root;
    }
};


// best solution
// worst case O(N) time complexity
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int idx = 0;
        return helper(preorder, idx, INT_MIN, INT_MAX);
    }
    
private:
    TreeNode* helper(const vector<int> &preorder, int &idx, int low, int high) {
        if(idx == preorder.size())
            return nullptr;
        
        int val = preorder[idx];
        if(val<low || val>high)  // node does not belong to current tree
            return nullptr;
        
        TreeNode *root = new TreeNode(val);
        ++idx;
        root->left = helper(preorder, idx, low, val);
        root->right = helper(preorder, idx, val, high);
        return root;
    }
};
