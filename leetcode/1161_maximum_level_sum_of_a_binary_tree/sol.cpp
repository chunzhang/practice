/*
Facebook/Microsoft/Amazon

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

Example 1:

Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Example 2:

Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5
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


// BFS
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        int ans = 0;
        int mval = INT_MIN;

        // BFS
        int level = 1;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int sz = q.size();
            int sum = 0;
            while(sz--) {
                TreeNode *node = q.front();
                q.pop();
                sum += node->val;
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
            if(sum > mval) {
                ans = level;
                mval = sum;
            }
            ++level;
        }

        return ans;
    }
};


// ref: DFS by tracking sum at leach level
class Solution {
public:
    void dfs(TreeNode* node, int level, vector<int>& sumOfNodesAtLevel) {
        if (node == nullptr) {
            return;
        }

        if (sumOfNodesAtLevel.size() == level) {
            sumOfNodesAtLevel.push_back(node->val);
        } else {
            sumOfNodesAtLevel[level] += node->val;
        }

        dfs(node->left, level + 1, sumOfNodesAtLevel);
        dfs(node->right, level + 1, sumOfNodesAtLevel);
    }

    int maxLevelSum(TreeNode* root) {
        vector<int> sumOfNodesAtLevel;
        dfs(root, 0, sumOfNodesAtLevel);

        int maxSum = INT_MIN;
        int ans = 0;

        for (int i = 0; i < sumOfNodesAtLevel.size(); i++) {
            if (maxSum < sumOfNodesAtLevel[i]) {
                maxSum = sumOfNodesAtLevel[i];
                ans = i + 1;
            }
        }

        return ans;
    }
};
