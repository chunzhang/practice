/*
Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

 

Example 1:

Input: root = [2,1,3]
Output: [2,1,3]
Example 2:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
0 <= Node.val <= 104
The input tree is guaranteed to be a binary search tree.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;


// based on preorder traversal, and uses stringstream
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        serializeHelper(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        int val;
        string sval;
        if(!(iss >> sval))
            val = -1;  // invalid value, i.e., no more nodes available
        else
            val = stoi(sval);
        return deserializeHelper(iss, val, INT_MIN, INT_MAX);
    }

private:
    void serializeHelper(TreeNode *root, ostringstream &oss) {
        if(!root)
            return;
        
        oss << root->val << " ";
        if(root->left)
            serializeHelper(root->left, oss);
        if(root->right)
            serializeHelper(root->right, oss);
    }
    
    TreeNode* deserializeHelper(istringstream &iss, int &val, int low, int high) {
        if(val == -1)
            return nullptr;
        
        if(val<low || val>high)
            return nullptr;
        
        TreeNode *root = new TreeNode(val);
        string sval;
        if(!(iss>>sval))
            val = -1;
        else
            val = stoi(sval);
        
        root->left = deserializeHelper(iss, val, low, root->val);
        root->right = deserializeHelper(iss, val, root->val, high);
        return root;
    }
};


// reference from HuaHua -- using binary format
class Codec {
public:
 
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        serialize(root, s);
        return s;
    }
 
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {        
        int pos = 0;
        return deserialize(data, pos, INT_MIN, INT_MAX);
    }
private:
    void serialize(TreeNode* root, string& s) {
        if (!root) return;    
        s.append(reinterpret_cast<const char*>(&root->val), sizeof(root->val));
        serialize(root->left, s);
        serialize(root->right, s);
    }
    
    TreeNode* deserialize(const string& s, int& pos, int curMin, int curMax) {
        if (pos >= s.size()) return nullptr;
        int val = *reinterpret_cast<const int*>(s.data() + pos);
        if (val < curMin || val > curMax) return nullptr;
        pos += sizeof(val);
        TreeNode* root = new TreeNode(val);
        root->left = deserialize(s, pos, curMin, val);
        root->right = deserialize(s, pos, val, curMax);
        return root;
    }
};
