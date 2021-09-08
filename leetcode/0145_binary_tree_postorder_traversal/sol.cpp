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
// Using stack and push_front of linkded list
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(!root)
            return {};
        
        deque<int> ans;
        stack<TreeNode*> st;
        st.push(root);
        while(st.size()) {
            TreeNode *node = st.top();
            st.pop();
            ans.push_front(node->val);
            if(node->left)
                st.push(node->left);
            if(node->right)
                st.push(node->right);
        }
        
        return vector<int>(ans.begin(), ans.end());
    }
};



// Using stack and vistied node marking
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root)
            return ans;
        
        stack<pair<TreeNode*,bool>> st;  // whether the node is visited before
        st.push({root,false});  // initially, root node is not visited before
        while(!st.empty()) {
            auto &elem = st.top();  // return reference so we can modify its value directly
            if(!elem.second) {  // node is visited for the first time
                elem.second = true;  // mark visited
                TreeNode *node = elem.first;
                if(node->right)
                    st.push({node->right,false});
                if(node->left)
                    st.push({node->left,false});
            }
            else {  // node is visited for the second time
                st.pop();
                ans.push_back(elem.first->val);
            }
        }
        
        return ans;
    }
};


// A better solution w/o caching visited nodes
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode *pCur = root;  // when pCur is not nullptr, it means we need to keep searching left
        TreeNode *pLast = nullptr;
        while(pCur || !s.empty()) {
            if(pCur) {
                s.push(pCur);
                pCur = pCur->left;
            }
            else {
                TreeNode *node = s.top();
                if(node->right              // traverse right before root in postorder
                   && node->right!=pLast    // avoid visiting same right node infinitely
                   ) {
                    pCur = node->right;       // assign pCur so we keep searching right subtree in the next iteration
                }
                else {
                    s.pop();
                    res.push_back(node->val);
                    pLast = node;  // make sure this node won't be visited again in the next iteration
                }
            }
        }

        return res;
    }

};

// Solution with extra cache for visited nodes
class Solution2 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root)
            return res;

        stack<TreeNode*> s;
        set<TreeNode*> visited;
        s.push(root);
        while(!s.empty()) {
            TreeNode *node = s.top();
            if(node->left && visited.find(node->left)==visited.end()) {
                s.push(node->left);
            }
            else if(node->right && visited.find(node->right)==visited.end()) {
                s.push(node->right);
            }
            else {
                s.pop();
                visited.insert(node);
                res.push_back(node->val);
            }
        }

        return res;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *root = makeTree(argc, argv);
    Solution sol;
    auto res = sol.postorderTraversal(root);
    printVector(res);

    return 0;
}
