/*
company
Facebook
company
Amazon
company
Apple

Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

Example 1:

Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:

Input: root = [2,1,3]
Output: [2,1,3]
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
1 <= Node.val <= 10^5
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


// re-build the tree from sorted numbers
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nums;
        inorder(root, nums);  

        // re-build balanced tree from sorted nums
        return build(nums,0,nums.size());
    }

private:
    void inorder(TreeNode *root, vector<int> &nums) {
        if(root->left)
            inorder(root->left, nums);
        nums.push_back(root->val);
        if(root->right)
            inorder(root->right, nums);
    }

    // [i,j) interval
    TreeNode* build(const vector<int> &nums, int i, int j) {
        if(i >= j)
            return nullptr;

        int mid = i + (j-i)/2;
        TreeNode *root = new TreeNode(nums[mid], build(nums,i,mid), build(nums,mid+1,j));
        return root;
    }
};
