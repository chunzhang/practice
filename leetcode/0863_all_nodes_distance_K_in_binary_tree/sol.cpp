/*
  Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

  You can return the answer in any order.

 

  Example 1:


  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
  Output: [7,4,1]
  Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
  Example 2:

  Input: root = [1], target = 1, k = 3
  Output: []
 

  Constraints:

  The number of nodes in the tree is in the range [1, 500].
  0 <= Node.val <= 500
  All the values Node.val are unique.
  target is the value of one of the nodes in the tree.
  0 <= k <= 1000
*/


// BFS to find up to K level
// time and space complexity: O(N)
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        // build graph: add edge to parent
        preorder(root, nullptr);
        
        // BFS
        unordered_set<TreeNode*> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited.insert(target);
        vector<int> ans;
        while(!q.empty() && k>=0) {
            int sz = q.size();
            while(sz--) {
                TreeNode *node = q.front();
                q.pop();
                if(k == 0) {
                    ans.push_back(node->val);  // no need to traversal further
                }
                else {
                    TreeNode *parent = _parent[node];
                    if(parent && visited.find(parent)==visited.end()) {
                        q.push(parent);
                        visited.insert(parent);
                    }
                    if(node->left && visited.find(node->left)==visited.end()) {
                        q.push(node->left);
                        visited.insert(node->left);
                    }
                    if(node->right && visited.find(node->right)==visited.end()) {
                        q.push(node->right);
                        visited.insert(node->right);
                    }
                }
            }
            --k;
        }
        
        return ans;
    }
    
private:
    unordered_map<TreeNode*, TreeNode*> _parent;
    void preorder(TreeNode *node, TreeNode *parent) {  // cache parent of each node
        if(parent)
            _parent[node] = parent;
        if(node->left)
            preorder(node->left, node);
        if(node->right)
            preorder(node->right, node);
    }
};


// BFS: ref impl from HuaHua
// since all node values are unique, we can use it as node ID
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        constexpr int kMaxN = 500 + 1;
        g = vector<vector<int>>(kMaxN);
        buildGraph(nullptr, root);
        vector<int> ans;
        vector<int> seen(kMaxN);    
        queue<int> q;
        seen[target->val] = 1;
        q.push(target->val);
        int k = 0;
        while (!q.empty() && k <= K) {
            int s = q.size();
            while (s--) {
                int node = q.front(); q.pop();
                if (k == K) ans.push_back(node);
                for (int child : g[node]) {
                    if (seen[child]) continue;
                    q.push(child);
                    seen[child] = 1;
                }
            }
            ++k;
        }
        return ans;
    }
private:  
    vector<vector<int>> g;
  
    void buildGraph(TreeNode* parent, TreeNode* child) {      
        if (parent) {
            g[parent->val].push_back(child->val);
            g[child->val].push_back(parent->val);
        }
        if (child->left) buildGraph(child, child->left);
        if (child->right) buildGraph(child, child->right);
    }
};


// Recursion: ref impl from HuaHua
// time and space complexity: O(N)
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        ans.clear();
        dis(root, target, K);
        return ans;
    }
private:
    vector<int> ans;
    // Returns the distance from root to target.
    // Returns -1 if target does not in the tree.
    int dis(TreeNode* root, TreeNode* target, int K) {
        if (root == nullptr) return -1;
        if (root == target) {
            collect(target, K);
            return 0;
        }
    
        int l = dis(root->left, target, K);
        int r = dis(root->right, target, K);
    
        // Target in the left subtree
        if (l >= 0) {
            if (l == K - 1) ans.push_back(root->val);
            // Collect nodes in right subtree with depth K - l - 2
            collect(root->right, K - l - 2);
            return l + 1;
        }
    
        // Target in the right subtree
        if (r >= 0) {
            if (r == K - 1) ans.push_back(root->val);
            // Collect nodes in left subtree with depth K - r - 2
            collect(root->left, K - r - 2);
            return r + 1;
        }
    
        return -1;
    }
  
    // Collect nodes that are d steps from root.
    void collect(TreeNode* root, int d) {
        if (root == nullptr || d < 0) return;
        if (d == 0) ans.push_back(root->val);
        collect(root->left, d - 1);
        collect(root->right, d - 1);
    }
};
