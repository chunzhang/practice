/*
You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.

Return the minimum number of cameras needed to monitor all nodes of the tree.

 

Example 1:


Input: root = [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.
Example 2:


Input: root = [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
Node.val == 0
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

// bottom-up DP using states
// O(N) time complexity
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        // dp(n, hasCamera, isCovered): min number of cameras needed of tree rooted at n, based on whether camera is put on n and whether n is covered
        // since it's impossible to have hasCamera==1&&isCovered==0, we can collapse into below states:
        // -- dp0(n): n is not covered (by camera put on its children)
        // -- dp1(n): n is covered (by camera put on its children), and does not have camera put on it
        // -- dp2(n): n is covered (by camera put on its children), and has camera put on it
        // Transition function
        // -- dp0(n) = dp1(n->left) + dp1(n->right)
        // -- dp1(n) = min{dp2(n->left)+min(dp1(n->right),dp2(n->right)), dp2(n->right)+min(dp1(n->left),dp2(n->left))}  // when left has camera, right can either have or not have camera; and vice versa
        // -- dp2(n) = 1 + min{dp0(n->eft),dp1(n->left),dp2(n->left)} + min{dp0(n->right),dp1(n->right),dp2(n->right)};
        // One can use post-order to solve the DP bottom-up
        
        vector<int> res = dp(root);
        return min(res[1], res[2]);
    }
    
private:
    // return {dp0, dp1, dp2}
    vector<int> dp(TreeNode *node) {
        if(!node)
            return {0,0,INT_MAX/2};  // this is important
        
        vector<int> left = dp(node->left);
        vector<int> right = dp(node->right);
        int lCovered = min(left[1],left[2]);    // either have or not have camera
        int rCovered = min(right[1],right[2]);  // either have or not have camera
        
        // transition
        int dp0 = left[1] + right[1];
        int dp1 = min(left[2]+rCovered/*left has camera*/, right[2]+lCovered/*right has camera*/);  // this will be INT_MAX/2 for leaf node
        // since camera is put on node, child does not need to havee been covered by its children, so we need to include dp0(node->left) and dp0(node->right) into calculation
        int dp2 = 1 + *min_element(left.begin(), left.end()) + *min_element(right.begin(), right.end());
        
        return {dp0, dp1, dp2};
    }
};


// greedy algorithm
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        // greedy: in bottom-up manner, only insert camera to the node that none of its children and parent are covered yet 
        _nCameras = 0;
        greedy(root, nullptr);
        return _nCameras;
    }

private:
    int _nCameras;
    enum STATE {NONE, CAMERA, COVERED};
    enum STATE greedy(TreeNode *node, TreeNode *parent) {
        if(!node)
            return COVERED;  // so we don't need to insert camera to leaf nodes (unless root is leaf node itself)
        
        STATE left = greedy(node->left, node);
        STATE right = greedy(node->right, node);
        
        if(left==NONE || right==NONE) {
            ++_nCameras;
            return CAMERA;
        }
        
        if(left==CAMERA || right==CAMERA)
            return COVERED;
        
        // upon reaching here, both children are in COVERED state
        if(!parent) {  // root cannot be covered by its parent, so we must put a camera on it
            ++_nCameras;
            return CAMERA;
        }
        
        return NONE;
    }
};


// greedy solution from HuaHua
enum class State { NONE = 0, COVERED = 1, CAMERA = 2 };
 
class Solution {
public:
  int minCameraCover(TreeNode* root) {        
    if (dfs(root) == State::NONE) ++ans_;
    return ans_;
  }
private:  
  int ans_ = 0;
  State dfs(TreeNode* root) {
    if (!root) return State::COVERED;
    State l = dfs(root->left);
    State r = dfs(root->right);
    if (l == State::NONE || r == State::NONE) {
      ++ans_;
      return State::CAMERA;
    }
    if (l == State::CAMERA || r == State::CAMERA)
      return State::COVERED;    
    return State::NONE;
  }
};


// official greedy sol (in Java)
class Solution {
    int ans;
    Set<TreeNode> covered;
    public int minCameraCover(TreeNode root) {
        ans = 0;
        covered = new HashSet();
        covered.add(null);

        dfs(root, null);
        return ans;
    }

    public void dfs(TreeNode node, TreeNode par) {
        if (node != null) {
            dfs(node.left, node);
            dfs(node.right, node);

            if (par == null && !covered.contains(node) ||
                    !covered.contains(node.left) ||
                    !covered.contains(node.right)) {
                ans++;
                covered.add(node);
                covered.add(par);
                covered.add(node.left);
                covered.add(node.right);
            }
        }
    }
};
