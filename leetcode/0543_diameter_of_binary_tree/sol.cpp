/*
  Given the root of a binary tree, return the length of the diameter of the tree.

  The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

  The length of a path between two nodes is represented by the number of edges between them.

 

  Example 1:


  Input: root = [1,2,3,4,5]
  Output: 3
  Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
  Example 2:

  Input: root = [1,2]
  Output: 1
 

  Constraints:

  The number of nodes in the tree is in the range [1, 104].
  -100 <= Node.val <= 100
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

// O(N) algorithm
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        _max = INT_MIN;
        longestPath(root);
        return _max;  
    }
    
private:
    int _max;
    // return number of nodes of longest path from node and downwards
    // also update global diameter max
    int longestPath(TreeNode *node) {
        if(!node)
            return 0;
        int l = longestPath(node->left);
        int r = longestPath(node->right);
        _max = max(_max, l+r);  // path-length = #nodes - 1
        return max(l,r)+1;
    }
};


// iterative approach (from HuaHua)
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {        
        if (!root) return 0;
        int ans = 0;
        unordered_map<TreeNode*, int> d{{nullptr, -1}};        
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* node = s.top();            
            if (d.count(node->left) && d.count(node->right)) {                
                int l = d[node->left] + 1;
                int r = d[node->right] + 1;
                ans = max(ans, l + r);
                d[node] = max(l, r);
                // children's results will never be used again, safe to delete here.
                if (node->left) d.erase(node->left);
                if (node->right) d.erase(node->right);
                s.pop();
            } else {
                if (node->left) s.push(node->left);
                if (node->right) s.push(node->right);
            }
        }
        return ans;
    }
};


// C++ / Floyd-Warshall (HuaHua)
// O(N^3) time complexity
// -- O(N^2) number of tree node pairs, i.e., paths
// -- For each path, needs O(N) to comptue shortest path (which is also the only path existing between the two nodes)
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;        
        edges_.clear();
        int n = 0;
        buildGraph(root, n, -1);        
        vector<vector<int>> d(n, vector<int>(n, n));
        for (int i = 0; i < n; ++i) d[i][i] = 0;
        for (const auto& pair : edges_)
            d[pair.first][pair.second] = 1;
        
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        
        int ans = INT_MIN;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (d[i][j] == n) continue;
                ans = max(ans, d[i][j]);
            }
        return ans;
    }
    
private:
    void buildGraph(TreeNode* node, int& id, int pid) {
        if (!node) return; 
        int node_id = id++;
        if (pid >= 0) {
            edges_.emplace_back(node_id, pid);
            edges_.emplace_back(pid, node_id);            
        }
        buildGraph(node->left, id, node_id);
        buildGraph(node->right, id, node_id);
    }            
    vector<pair<int,int>> edges_;
};
