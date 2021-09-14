/*
Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [1,null,2,2]
Output: [2]
Example 2:

Input: root = [0]
Output: [0]
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5
 

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
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

// this works because inorder is sorted
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        // becuae inorder is sorted, we can count occurrence of each number using O(1) space (w/o counting stack for recursion)
        inorder(root);
        update();  // important to update last number
        return _ans;
    }
    
private:
    vector<int> _ans;
    int _num = 0;    // current number
    int _count = 0;  // count of current number
    int _maxCount = 0;  // max count so far
    TreeNode *_prev;
    
    void inorder(TreeNode *node) {
        if(node->left)
            inorder(node->left);
        
        if(_prev && node->val==_prev->val)
            ++_count;
        else {
            update();
            _num = node->val;
            _count = 1;
        }
        _prev = node;
        
        if(node->right)
            inorder(node->right);
    }
    
    // udpate answer
    void update() {
        if(_count == _maxCount)
            _ans.push_back(_num);
        else if(_count > _maxCount) {
            _ans.clear();
            _ans.push_back(_num);
            _maxCount = _count;
        }
    }
};
