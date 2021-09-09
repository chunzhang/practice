/*
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
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


// BFS, use queue only
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        
        // BFS
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        while(!q.empty()) {
            ans.push_back({});
            int sz = q.size();
            while(sz--) {
                TreeNode *node = q.front();
                q.pop();
                ans.back().push_back(node->val);
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
        }
        
        
        return ans;
    }
};


// DFS, preorder
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)
            return ans;
        // DFS, preorder
        preorder(root, 0, ans);
        return ans;
    }
    
private:
    void preorder(TreeNode *node, int lv, vector<vector<int>> &ans) {
        if(lv >= ans.size())
            ans.resize(lv+1);
        ans[lv].push_back(node->val);
        if(node->left)
            preorder(node->left, lv+1, ans);
        if(node->right)
            preorder(node->right, lv+1, ans);
    }
};


// BFS, use rolling vector
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root)
            return res;
        vector<TreeNode*> curLevel{root};
        while(!curLevel.empty()) {
            vector<int> level;
            vector<TreeNode*> nextLevel;
            for(TreeNode *node : curLevel) {
                level.push_back(node->val);
                if(node->left)
                    nextLevel.push_back(node->left);
                if(node->right)
                    nextLevel.push_back(node->right);
            }
            res.push_back(level);
            curLevel.swap(nextLevel);
        }

        return res;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *root = makeTree(argc, argv);
    Solution sol;
    auto res = sol.levelOrder(root);
    printMatrix(res);

    return 0;
}
