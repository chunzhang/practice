/*
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

 

Example 1:


Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:


Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 104
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


// DP form 1: depends on children and grandchildren
// O(N) time complexity, O(N) space complexity
class Solution {
public:
    int rob(TreeNode* root) {
        // dp(n): max benefit up to node n
        // dp(n) = max{dp(children), n->val+dp(grandchildren)}
        // bottom up build ==> postorder traversal
        return dp(root);
    }
    
private:
    unordered_map<TreeNode*,int> _dp;  // because of the need to access grandchildren results
    int dp(TreeNode *node) {
        if(!node)
            return 0;
        int l = dp(node->left);
        int r = dp(node->right);
        int ll = node->left?_dp[node->left->left]:0;
        int lr = node->left?_dp[node->left->right]:0;
        int rl = node->right?_dp[node->right->left]:0;
        int rr = node->right?_dp[node->right->right]:0;
        int benefit = max(l+r/*not rob node*/, node->val+ll+lr+rl+rr);
        _dp[node] = benefit;
        return benefit;
    }
};


// A better DP formulation based on states: whether the house is robbed or not
// O(N) time complexity, O(h) space complexity, where h is max height of the tree
class Solution {
public:
    int rob(TreeNode* root) {
        // dp0(n): max benefit up to node n when n is not robbed
        // dp1(n): max benefit up to node n when n is robbed
        // dp0(n) = max(dp0(n->left), dp1(n->left)) + max(dp0(n->right), dp1(n->right))
        // dp1(n) = n->val + dp0(n->left) + dp0(n->right)
        // Using postorder traversal, we can build this bottom-up
        pair<int,int> benefit = dp(root);
        return max(benefit.first, benefit.second);
    }
    
private:
    // returns {dp0,dp1} pair
    pair<int,int> dp(TreeNode *node) {
        if(!node)
            return {0,0};
        pair<int,int> left = dp(node->left);
        pair<int,int> right = dp(node->right);
        int dp0 = max(left.first,left.second) + max(right.first,right.second);
        int dp1 = node->val + left.first + right.first;
        return {dp0,dp1};
    }
};


// just one ref impl from HuaHua
class Solution {
public:
  int rob(TreeNode* root) {
    int l = 0;
    int r = 0;
    return rob(root, l, r);    
  }
private:
  // return rob(root) and stores rob(root->left/right) in l/r.
  int rob(TreeNode* root, int& l, int& r) {
    if (root == nullptr) return 0;
    int ll = 0;
    int lr = 0;
    int rl = 0;
    int rr = 0;
    l = rob(root->left, ll, lr);
    r = rob(root->right, rl, rr);    
    return max(root->val + ll + lr + rl + rr, l + r);
  }
};
