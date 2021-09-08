#include "../common/common.h"
#include <stack>
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
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> st;
        TreeNode *pCur = root;
        while(pCur || st.size()) {
            while(pCur) {  // points to left most unvisited node
                st.push(pCur);
                pCur = pCur->left;
            }
            
            // up to here, everything on the left has been visited
            pCur = st.top();
            st.pop();
            ans.push_back(pCur->val);
            pCur = pCur->right;
        }
        return ans;
    }
};

// my newest solution that mimics the recursion with stack
// not very runtime and space efficient, since each node will be pushed and poped twice, but code is straightforward to understand
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root)
            return ans;
        
        // use stack to mimic recursion
        stack<pair<TreeNode*,bool>> st;  // for each tree node, record whether it is encountered for the first time
        st.push({root,true});
        while(!st.empty()) {
            TreeNode *node = st.top().first;  // we guarantee that no NULL node is pushed
            bool first = st.top().second;
            st.pop();
            if(!first) {
                ans.push_back(node->val);
            }
            else {  // first time, we need to push its child to keep in-order
                if(node->right)
                    st.push({node->right, true});
                st.push({node, false});
                if(node->left)
                    st.push({node->left,true});
            }
        }
        
        return ans;
    }
};

// A better solution w/o extra visited node cache
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode *pCur = root;
        while(pCur || !s.empty()) {
            if(pCur) {
                s.push(pCur);
                pCur = pCur->left;
            }
            else {  
                pCur = s.top();  // upon here, the left tree of pCur has already been processed
                s.pop();
                res.push_back(pCur->val);
                pCur = pCur->right;
            }
        }

        return res;
    }

};


class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root)
            return res;

        set<TreeNode*> visited;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()) {
            TreeNode *node = stk.top();
            if(node->left && visited.find(node->left)==visited.end()) {
                stk.push(node->left);
                continue;
            }

            res.push_back(node->val);
            stk.pop();
            visited.insert(node);
      
            if(node->right && visited.find(node->right)==visited.end())
                stk.push(node->right);
        }

        return res;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *root = makeTree(argc, argv);
    Solution sol;
    auto res = sol.inorderTraversal(root);
    printVector(res);

    return 0;
}
