/*
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any path.

 

Example 1:


Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
Example 2:


Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000
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


// most recent impl
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        dfs(root, ans);
        return ans;
    }
    
private:
    // return max sum from current node and downwards, i.e., uni-direction
    int dfs(TreeNode *node, int &ans) {
        if(!node)
            return 0;
        
        int left = dfs(node->left, ans);
        int right = dfs(node->right, ans);
        int sum = node->val + (left>0?left:0) + (right>0?right:0);
        ans = max(ans, sum);
        return max(node->val, node->val+max(left,right));
    }
};

// O(N) algorithm
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return dfs(root).second;
    }
    
private:
    // for each node, we calculate:
    // 1. max sum starting from node and downwards
    // 2. max path sum rooted at node (path not necessarily going through node)
    pair<int,int> dfs(TreeNode *node) {
        if(!node)
            return {0,INT_MIN};
        
        pair<int,int> left = dfs(node->left);
        pair<int,int> right = dfs(node->right);
        int lDown = left.first;   // max sum of node-->left path (downwards only)
        int lTree = left.second;  // max path sum of left tree (path does not necessarily go through left node)
        int rDown = right.first;
        int rTree = right.second;
        
        int curDown = max(lDown>0?lDown:0,rDown>0?rDown:0) + node->val;
        int curTree = max(lTree, rTree);     // path not going through current node
        curTree = max(curTree, (lDown>0?lDown:0)+(rDown>0?rDown:0)+node->val);  // path going through current node
        return {curDown,curTree};
    }
};


// a simplified version, but fundamental idea is the same
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        _max = INT_MIN;
        dfs(root);
        return _max;
    }
    
private:
    int _max;
    // returns max sum of the path from node and downwards
    // also, we compute the max sum of path going through node as subtree root 
    // since the global max path sum comes from one of the original tree node, we can keep global max as the result
    int dfs(TreeNode *node) {
        if(!node)
            return 0;
        
        int left = dfs(node->left);
        if(left < 0)
            left = 0;
        int right = dfs(node->right);
        if(right < 0)
            right = 0;
        
        int cur = max(left, right) + node->val;  // max sum of path from node and downwards
        _max = max(_max, left+right+node->val);  // max sum of path going through node
        
        return cur;
    }
};
