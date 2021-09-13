/*
Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

 

Example 1:


Input: root = [4,2,6,1,3]
Output: 1
Example 2:


Input: root = [1,0,48,null,null,12,49]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 104].
0 <= Node.val <= 105
*/

// inorder traversal, by keeping prev node
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        _prev = nullptr;
        _minDiff = INT_MAX;
        inorder(root);
        return _minDiff;
    }
    
private:
    TreeNode *_prev;
    int _minDiff;
    void inorder(TreeNode *node) {
        if(node->left)
            inorder(node->left);
        
        if(_prev)
            _minDiff = min(_minDiff, node->val-_prev->val);
        _prev = node;
        
        if(node->right)
            inorder(node->right);
    }
};


// inorder traversal -- iterative
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int ans = INT_MAX;
        // iterative method using stack
        TreeNode *pCur = root;
        TreeNode *pPrev = nullptr;
        stack<TreeNode*> st;
        while(pCur || !st.empty()) {
            while(pCur) {
                st.push(pCur);
                pCur = pCur->left;
            }
            
            pCur = st.top();
            st.pop();
            if(pPrev)
                ans = min(ans, pCur->val-pPrev->val);
            pPrev = pCur;
            
            pCur = pCur->right;
        }
        
        return ans;
    }
};
