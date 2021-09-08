/*
  Given the root of a binary tree, calculate the vertical order traversal of the binary tree.

  For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).

  The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.

  Return the vertical order traversal of the binary tree.

 

  Example 1:


  Input: root = [3,9,20,null,null,15,7]
  Output: [[9],[3,15],[20],[7]]
  Explanation:
  Column -1: Only node 9 is in this column.
  Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
  Column 1: Only node 20 is in this column.
  Column 2: Only node 7 is in this column.
  Example 2:


  Input: root = [1,2,3,4,5,6,7]
  Output: [[4],[2],[1,5,6],[3],[7]]
  Explanation:
  Column -2: Only node 4 is in this column.
  Column -1: Only node 2 is in this column.
  Column 0: Nodes 1, 5, and 6 are in this column.
  1 is at the top, so it comes first.
  5 and 6 are at the same position (2, 0), so we order them by their value, 5 before 6.
  Column 1: Only node 3 is in this column.
  Column 2: Only node 7 is in this column.
  Example 3:


  Input: root = [1,2,3,4,6,5,7]
  Output: [[4],[2],[1,5,6],[3],[7]]
  Explanation:
  This case is the exact same as example 2, but with nodes 5 and 6 swapped.
  Note that the solution remains the same since 5 and 6 are in the same location and should be ordered by their values.
 

  Constraints:

  The number of nodes in the tree is in the range [1, 1000].
  0 <= Node.val <= 1000
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

// Preorder traversal, using many aux data structures
// O(NlgN) time complexity, as each node needs to be inserted to a map
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int,map<int,vector<int>>> arrays;  // column --> level --> array
        preorder(root,0,0,arrays);
        
        vector<vector<int>> ans;
        for(auto it=arrays.begin(); it!=arrays.end(); ++it) {  // for each column
            vector<int> vCol;
            auto &byLevel = it->second;
            for(auto it2=byLevel.begin(); it2!=byLevel.end(); ++it2) {  // for each level
                auto &sub = it2->second;
                sort(sub.begin(), sub.end());  // at each level, sort by values
                for(auto num : sub)
                    vCol.push_back(num);
            }
            ans.push_back(vCol);
        }
        return ans;
    }
    
private:
    // use pre-order traversal to collect results
    void preorder(TreeNode *node, int lv, int col, map<int,map<int,vector<int>>> &arrays) {
        if(!node)
            return;
        arrays[col][lv].push_back(node->val);
        if(node->left)
            preorder(node->left, lv+1, col-1, arrays);
        if(node->right)
            preorder(node->right, lv+1, col+1, arrays);
    }
};


// A different solution by keeping column-->list of (level,value) mapping
// assume there's k columns, then it is O(k*(N/k)*log(N/k)) = O(N*lg(N/k)) sorting, i.e., time complexity
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        unordered_map<int, vector<pair<int,int>>> cols;  // column --> (level,value) mapping
        int minCol = 0;
        int maxCol = 0;
        preorder(root, 0, 0, cols, minCol, maxCol);
        
        // construct results
        vector<vector<int>> ans;
        auto myComp = [](const pair<int,int> &p1, const pair<int,int> &p2) {  // sort by level first, and then by value
            if(p1.first!=p2.first)
                return p1.first < p2.first;
            else
                return p1.second < p2.second;
            };
        for(int c=minCol; c<=maxCol; ++c) {  // each iteration is O((N/k)*lg(N/k)) time complexity, i.e., bounded by sorting
            auto it = cols.find(c);
            if(it == cols.end())
                continue;
            auto &v = it->second;
            sort(v.begin(), v.end(), myComp);
            vector<int> vCol;
            for(auto &elem : v)
                vCol.push_back(elem.second);
            ans.push_back(vCol);
        }
        
        return ans;
    }
    
private:
    // use pre-order traversal to collect results
    void preorder(TreeNode *node, int lv, int col, unordered_map<int, vector<pair<int,int>>> &cols, int &minCol, int &maxCol) {
        cols[col].push_back({lv,node->val});
        minCol = min(minCol, col);
        maxCol = max(maxCol, col);
        if(node->left)
            preorder(node->left, lv+1, col-1, cols, minCol, maxCol);
        if(node->right)
            preorder(node->right, lv+1, col+1, cols, minCol, maxCol);
    }
};

// reference solution from HuaHua
// O(NlgN) time complexity, as each node needs to be inserted to a map
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        int min_x = INT_MAX;
        int max_x = INT_MIN;
        map<pair<int, int>, set<int>> h; // {y, x} -> {vals}
        traverse(root, 0, 0, h, min_x, max_x);
        vector<vector<int>> ans(max_x - min_x + 1);
        for (const auto& m : h) {      
            int x = m.first.second - min_x;
            ans[x].insert(end(ans[x]), begin(m.second), end(m.second));
        }
        return ans;
    }
private:
    void traverse(TreeNode* root, int x, int y, 
                  map<pair<int, int>, set<int>>& h,
                  int& min_x,
                  int& max_x) {
        if (!root) return;
        min_x = min(min_x, x);
        max_x = max(max_x, x);    
        h[{y, x}].insert(root->val);
        traverse(root->left, x - 1, y + 1, h, min_x, max_x);
        traverse(root->right, x + 1, y + 1, h, min_x, max_x);
    }
};
