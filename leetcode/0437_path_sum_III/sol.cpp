/*
Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).

 

Example 1:


Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.
Example 2:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: 3
 

Constraints:

The number of nodes in the tree is in the range [0, 1000].
-10^9 <= Node.val <= 10^9
-1000 <= targetSum <= 1000
*/

// brute-force: try every starting point of the path, i.e., each tree node can be a starting point
// T(N) = O(N) + 2*T(N/2)
// ==> O(NlgN) time complexity?
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if(!root)
            return 0;
        int ans = 0;
        psum(root, targetSum, ans);  // using root
        if(root->left)
            ans += pathSum(root->left, targetSum);
        if(root->right)
            ans += pathSum(root->right, targetSum);
        
        return ans;
    }
    
private:
    // when current node is used, how many paths sum up to target
    void psum(TreeNode *node, int target, int &ans) {
        if(node->val == target)
            ++ans;
        if(node->left)
            psum(node->left, target-node->val, ans);
        if(node->right)
            psum(node->right, target-node->val, ans);
    }
};


// based on prefix-sum along the current path
// O(N) time complexity
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if(!root)
            return 0;
        
        int ans = 0;
        unordered_map<int,int> count;   // prefix-sum --> count mapping
        dfs(root, targetSum, 0, ans, count);
        return ans;
    }
    
private:
    // for each call, add up the number of satisfied path the ends up with the node
    void dfs(TreeNode *node, int target, int psum/*prefix sum along the path*/, int &ans, unordered_map<int,int> &count) {
        psum += node->val;
        if(psum == target)  // full path that starts with tree root
            ++ans;
        ans += count[psum-target];  // partial path that does not start with tree root
        ++count[psum];  // this cannot be added earlier, as we want to find number of nodes prior than current node, that have prefix-sum of psum-target
        if(node->left)
            dfs(node->left, target, psum, ans, count);
        if(node->right)
            dfs(node->right, target, psum, ans, count);
        --count[psum];
    }
};
