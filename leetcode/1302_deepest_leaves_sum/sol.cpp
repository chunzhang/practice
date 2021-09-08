/*
Given the root of a binary tree, return the sum of values of its deepest leaves.
 

Example 1:


Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
Example 2:

Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
Output: 19
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
1 <= Node.val <= 100
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

// pre-order traversal, i.e., compute sum by each level
class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        if(!root)
            return -1;
        
        vector<int> sums(1e4, 0);  // sum by level
        int maxLv = 0;
        preorder(root, 0, sums, maxLv);
        return sums[maxLv];
    }
    
private:
    void preorder(TreeNode *node, int lv, vector<int> &sums, int &maxLv) {
        sums[lv] += node->val;
        maxLv = max(maxLv, lv);
        if(node->left)
            preorder(node->left, lv+1, sums, maxLv);
        if(node->right)
            preorder(node->right, lv+1, sums, maxLv);
    }
};

// a better O(1) space solution, i.e, only track sum of current known max-level
class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        if(!root)
            return -1;
        
        int maxLv = 0;
        int sum = 0;  // sum of maxLv
        preorder(root, 0, sum, maxLv);
        return sum;
    }
    
private:
    void preorder(TreeNode *node, int lv, int &sum, int &maxLv) {
        if(lv > maxLv) {
            maxLv = lv;
            sum = 0;
        }
  
        if(lv == maxLv)
            sum += node->val;

        if(node->left)
            preorder(node->left, lv+1, sum, maxLv);
        if(node->right)
            preorder(node->right, lv+1, sum, maxLv);
    }
};
