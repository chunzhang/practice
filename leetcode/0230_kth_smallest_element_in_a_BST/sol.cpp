/*
Given the root of a binary search tree, and an integer k, return the kth (1-indexed) smallest element in the tree.

 

Example 1:


Input: root = [3,1,4,null,2], k = 1
Output: 1
Example 2:


Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 104
0 <= Node.val <= 104
 

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
*/

// most concise recursive impl
// O(H+k) time complexity, where H is height of the tree?
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        return inorder(root, k);
    }
    
private:
    int inorder(TreeNode *node, int &k) {
        if(!node)
            return -1;
        
        int left = inorder(node->left, k);
        if(!k)
            return left;
        if(--k == 0)
            return node->val;
        return inorder(node->right, k);
    }
};

// recursive impl 1
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        _ans = -1;
        _remaining = k;
        inorder(root);
        return _ans;
    }
    
private:
    int _ans;
    int _remaining;
    void inorder(TreeNode *node) {
        if(node->left)
            inorder(node->left);
        
        if(!_remaining)
            return;
        
        --_remaining;
        if(!_remaining)
            _ans = node->val;
        else if(node->right)
            inorder(node->right);
    }
};


// recursive impl 2
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int val = 0;
        int count = 0;
        if(root) {
            helper(root, val, count, k);
        }
        return val;
    }
    
    bool helper(TreeNode *root, int &val, int &count, int k) {
        if(root->left && helper(root->left, val, count, k))
            return true;
        if(++count == k) {
            val = root->val;
            return true;
        }
        if(root->right && helper(root->right, val, count, k))
            return true;
        return false;
    }
};


// iterative approach
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        // iterative
        TreeNode *pCur = root;
        stack<TreeNode*> st;
        while(pCur || !st.empty()) {
            while(pCur) {
                st.push(pCur);
                pCur = pCur->left;
            }
            
            pCur = st.top();
            st.pop();
            if(--k == 0)
                return pCur->val;
            pCur = pCur->right;
        }
        
        return -1;  // should not reach here if answer exists
    }
};
