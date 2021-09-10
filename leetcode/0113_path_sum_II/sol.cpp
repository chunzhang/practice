/*
Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.

 

Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22
Example 2:


Input: root = [1,2,3], targetSum = 5
Output: []
Example 3:

Input: root = [1,2], targetSum = 0
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
*/

#include "../common/common.h"

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// DFS impl 1
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        if(root)
            dfs(root, 0, targetSum, path, ans);
        return ans;
    }
    
private:
    void dfs(TreeNode *node, int sum, int targetSum, vector<int> &path, vector<vector<int>> &ans) {
        sum += node->val;
        path.push_back(node->val);
        if(!node->left && !node->right && sum==targetSum)
            ans.push_back(path);
        
        if(node->left)
            dfs(node->left, sum, targetSum, path, ans);
        if(node->right)
            dfs(node->right, sum, targetSum, path, ans);
        
        path.pop_back();
    }
};


// DFS impl 2
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> paths;
        vector<int> path;
        if(root)
            search(root, sum, path, paths);
        return paths;
    }

    void search(TreeNode *root, int sum, vector<int> &path, vector<vector<int>> &paths) {
        if(!root->left && !root->right && root->val==sum) {
            path.push_back(root->val);
            paths.push_back(path);
            path.pop_back();
            return;
        }

        path.push_back(root->val);
        if(root->left)
            search(root->left, sum-root->val, path, paths);
        if(root->right)
            search(root->right, sum-root->val, path, paths);
        path.pop_back();
    }
};

int main(int argc, char *argv[])
{
    TreeNode *root = makeTree(argc-1, argv);
    int sum = atoi(argv[argc-1]);
    Solution sol;
    auto paths = sol.pathSum(root, sum);
    printMatrix(paths);

    return 0;
}
