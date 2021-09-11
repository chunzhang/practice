/*
Given the root of a binary tree, return the most frequent subtree sum. If there is a tie, return all the values with the highest frequency in any order.

The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).

 

Example 1:


Input: root = [5,2,-3]
Output: [2,-3,4]
Example 2:


Input: root = [5,2,-5]
Output: [2]
 

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


class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        _maxFreq = 0;
        if(root)
            subSum(root);
        
        
        vector<int> ans;
        for(auto it=_count.begin(); it!=_count.end(); ++it) {
            if(it->second == _maxFreq)
                ans.push_back(it->first);
        }
        
        return ans;
    }
    
private:
    unordered_map<int, int> _count;
    int _maxFreq;
    int subSum(TreeNode *node) {
        int sum = node->val;
        if(node->left)
            sum += subSum(node->left);
        if(node->right)
            sum += subSum(node->right);
        
        _maxFreq = max(_maxFreq, ++_count[sum]);
        return sum;
    }
};
