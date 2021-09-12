/*
You are given the root of a binary tree with n nodes where each node in the tree has node.val coins. There are n coins in total throughout the whole tree.

In one move, we may choose two adjacent nodes and move one coin from one node to another. A move may be from parent to child, or from child to parent.

Return the minimum number of moves required to make every node have exactly one coin.

 

Example 1:


Input: root = [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
Example 2:


Input: root = [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root [taking two moves]. Then, we move one coin from the root of the tree to the right child.
Example 3:


Input: root = [1,0,2]
Output: 2
Example 4:


Input: root = [1,0,0,null,3]
Output: 4
 

Constraints:

The number of nodes in the tree is n.
1 <= n <= 100
0 <= Node.val <= n
The sum of all Node.val is n.
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

// distribute coins in postorder
// O(N) time complexity
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        return distribute(root, nullptr);
    }

private:
    // at each node, first distribute coins in left and right subtree (postorder)
    // and then send or borrow coins to parent
    // return number of moves to make the tree starting from node valid
    int distribute(TreeNode *node, TreeNode *parent) {
        if(!node)
            return 0;
        
        // first, distribute both subtrees to make each node contain one coin only
        int left = distribute(node->left, node);
        int right = distribute(node->right, node);
        
        // need to send or borrow delta number of coins to parent
        int delta = node->val - 1;
        if(parent) 
            parent->val += delta;
        else
            assert(node->val==1);  // it guarantees that the coin exists
        
        return abs(delta)+left+right;
    }
};


// a simpler impl, but same concept
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        _moves = 0;
        moveCoins(root);
        return _moves;
    }
    
private:
    int _moves;
    // return number of coins needed to send or borrow (from node to its parent)
    int moveCoins(TreeNode *node) {
        if(!node)
            return 0;
        int left = moveCoins(node->left);
        int right = moveCoins(node->right);
        _moves += abs(left) + abs(right);  // these number of coins need to be moved between node and left/right
        return node->val - 1 + left + right;  // number of coins need to be moved between node and its parent
    }
};
