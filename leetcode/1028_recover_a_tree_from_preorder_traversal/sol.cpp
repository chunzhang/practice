/*
Facebook

We run a preorder depth-first search (DFS) on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth of the root node is 0.

If a node has only one child, that child is guaranteed to be the left child.

Given the output traversal of this traversal, recover the tree and return its root.

Example 1:

Input: traversal = "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

Example 2:

Input: traversal = "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]

Example 3:

Input: traversal = "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 

Constraints:

The number of nodes in the original tree is in the range [1, 1000].
1 <= Node.val <= 10^9
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


// DFS with stack
// -- write helper function to extract next node's value and depth
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        int cur = 0;  // index to search the next node from the "traversal" string
        auto valAndLevel = getNode(traversal, cur);
        TreeNode *root = new TreeNode(valAndLevel.first);
        stack<pair<TreeNode*,int>> st;
        st.emplace(root,0);  // root is guaranteed to have level 0
        while(cur < traversal.size()) {
            valAndLevel = getNode(traversal, cur);
            while(st.top().second >= valAndLevel.second)  // stack top is not the parent as level does not match
                st.pop();
            TreeNode *parent = st.top().first;
            TreeNode *node = new TreeNode(valAndLevel.first);
            if(parent->left == nullptr)
                parent->left = node;
            else
                parent->right = node;
            st.emplace(node,valAndLevel.second); 
        }

        return root;
    }

private:
    // get the next (node-val, level) pair from the string
    pair<int,int> getNode(string &traversal, int &cur) {
        int level = 0;
        while(cur<traversal.size() && traversal[cur]=='-') {
            ++level;
            ++cur;
        }

        int val = 0;
        while(cur<traversal.size() && traversal[cur]!='-') {
            val = val*10 + traversal[cur] - '0';
            ++cur;
        }

        return {val,level};
    }
};


// same idea, but actually, we don't need to book keep level into the stack
// -- instead, we can use the stack's size to make the decision
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        int cur = 0;
        auto valAndLevel = getNode(traversal, cur);
        TreeNode *root = new TreeNode(valAndLevel.first);
        stack<TreeNode*> st;
        st.push(root);  // root is guaranteed to have level 0
        while(cur < traversal.size()) {
            valAndLevel = getNode(traversal, cur);
            while(st.size() > valAndLevel.second)  // we can use stack size to match level
                st.pop();
            TreeNode *parent = st.top();
            TreeNode *node = new TreeNode(valAndLevel.first);
            if(parent->left == nullptr)
                parent->left = node;
            else
                parent->right = node;
            st.push(node); 
        }

        return root;
    }

private:
    // get the next (node-val, level) pair from the string
    pair<int,int> getNode(string &traversal, int &cur) {
        int level = 0;
        while(cur<traversal.size() && traversal[cur]=='-') {
            ++level;
            ++cur;
        }

        int val = 0;
        while(cur<traversal.size() && traversal[cur]!='-') {
            val = val*10 + traversal[cur] - '0';
            ++cur;
        }

        return {val,level};
    }
};
