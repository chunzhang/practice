/*
Facebook/Amazon/Coupang

Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target. If there are multiple answers, print the smallest.

 

Example 1:


Input: root = [4,2,5,1,3], target = 3.714286
Output: 4
Example 2:

Input: root = [1], target = 4.428571
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 109
-109 <= target <= 109
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


// leftTree < root < rightTree
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        if(root->val == target)
            return root->val;
        else if(target < root->val) {
            if(!root->left)
                return root->val;
            int left = closestValue(root->left,target);
            return (abs(root->val-target)<abs(left-target))?root->val:left;
        }
        else {
            if(!root->right)
                return root->val;
            int right = closestValue(root->right,target);
            return (abs(root->val-target)<=abs(right-target))?root->val:right;
        }
    }
};


// iterative approach
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int ans = root->val;
        while(root) {
            int curVal = root->val;
            if(curVal == target)
                return curVal;
            if(abs(curVal-target)<abs(ans-target) || abs(curVal-target)==abs(ans-target)&&curVal<ans)
                ans = curVal;
            root = (target<curVal)?root->left:root->right;
        }

        return ans;
    }
};
