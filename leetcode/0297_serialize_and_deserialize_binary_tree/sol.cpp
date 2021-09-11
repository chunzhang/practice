/*
  Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

  Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

  Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 
  Example 1:


  Input: root = [1,2,3,null,null,4,5]
  Output: [1,2,3,null,null,4,5]
  Example 2:

  Input: root = []
  Output: []
  Example 3:

  Input: root = [1]
  Output: [1]
  Example 4:

  Input: root = [1,2]
  Output: [1,2]
 

  Constraints:

  The number of nodes in the tree is in the range [0, 10^4].
  -1000 <= Node.val <= 1000
*/

#include "../common/common.h"

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

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));


// DFS using stringstream
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        serializeDfs(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        return deserializeDfs(iss);
    }
    
private:
    void serializeDfs(TreeNode *root, ostringstream &oss) {
        if(!root) {
            oss << "N ";
            return;
        }
        
        oss << root->val << " ";  // use space as separator, so it can be handled by istringstream automatically
        serializeDfs(root->left, oss);
        serializeDfs(root->right, oss);
    }
    
    TreeNode* deserializeDfs(istringstream &iss) {
        string val;
        iss >> val;
        if(val == "N")
            return nullptr;
        
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserializeDfs(iss);
        root->right = deserializeDfs(iss);
        return root;
    }
};


// BFS impl 1
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // BFS
        string data;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if(node) {
                data += to_string(node->val);
                q.push(node->left);
                q.push(node->right);
            }
            else {
                data.push_back('N');
            }
            data.push_back('_');
        }
        
        // remove trailing nulls
        int end = data.size() - 2;
        while(end>=0 && data[end]=='_' && data[end+1]=='N')
            end -= 2;
        data.resize(end+2);
        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // split data by '_'
        vector<string> vals;
        int cur = 0;
        int sep = data.find_first_of('_', cur);
        while(sep != string::npos) {
            vals.push_back(data.substr(cur, sep-cur));
            cur = sep + 1;
            sep = data.find_first_of('_', cur);
        }
        
        // build tree
        vector<TreeNode*> nodes(vals.size(), nullptr);
        if(vals[0] != "N")
            nodes[0] = new TreeNode(stoi(vals[0]));
        int count = 0;  // count of null nodes so far
        for(int i=0; i<vals.size(); ++i) {  // create and link children
            if(!nodes[i]) {
                ++count;
                continue;
            }
            int il = (i-count)*2 + 1;  // index to left child
            int ir = (i-count)*2 + 2;  // index to right child
            if(il<vals.size() && vals[il]!="N") {
                TreeNode *left = new TreeNode(stoi(vals[il]));
                nodes[i]->left = left;
                nodes[il] = left;
            }
            if(ir<vals.size() && vals[ir]!="N") {
                TreeNode *right = new TreeNode(stoi(vals[ir]));
                nodes[i]->right = right;
                nodes[ir] = right;
            }
        }
        
        return nodes[0];
    }
};


// BFS impl 2
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        if(!root)
            return s;
        
        // Based on levelization
        queue<TreeNode*> q;
        q.push(root);
        int nValid = root ? 1 : 0;  // number of non-null node in the queue
        while(!q.empty() && nValid) {
            TreeNode *node = q.front();
            q.pop();
            if(node) {
                --nValid;
                s += to_string(node->val) + "@";
                q.push(node->left);
                nValid += node->left ? 1 : 0;
                q.push(node->right);
                nValid += node->right ? 1 : 0;
            }
            else {
                s += "null@";
            }
        }
        
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> inputs;
        size_t cur = 0;
        while(1) {
            size_t pos = data.find_first_of("@", cur);
            if(pos == string::npos)
                break;
            inputs.push_back(data.substr(cur, pos-cur));
            cur = pos + 1;
        }
        
        if(inputs.empty())
            return nullptr;
               
        vector<TreeNode*> nodes(inputs.size(), nullptr);
        nodes[0] = new TreeNode(stoi(inputs[0]));
        // Total number of null nodes seen so far -- used to adjust left/right child index since this is not a full binary tree
        int skip = 0;
        for(int i=0; i<inputs.size(); ++i) {
            if(inputs[i] == "null") {
                ++skip;
                continue;
            }
            TreeNode *cur = nodes[i];
            int leftIdx = 2*(i-skip) + 1;
            if(leftIdx<inputs.size() && inputs[leftIdx]!="null") {
                TreeNode *leftNode = new TreeNode(stoi(inputs[leftIdx]));
                cur->left = leftNode;
                nodes[leftIdx] = leftNode;
            }
            int rightIdx = 2*(i-skip) + 2;
            if(rightIdx<inputs.size() && inputs[rightIdx]!="null") {
                TreeNode *rightNode = new TreeNode(stoi(inputs[rightIdx]));
                cur->right = rightNode;
                nodes[rightIdx] = rightNode;
            }
        }
        
        return nodes[0];
    }
};

// Also BFS (i.e., levelized traversal), but with a better way to deserialize using queue as well
class Codec2 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        if(!root)
            return s;
        
        // Based on levelization
        queue<TreeNode*> q;
        q.push(root);
        int nValid = root ? 1 : 0;  // number of non-null node in the queue
        while(!q.empty() && nValid) {
            TreeNode *node = q.front();
            q.pop();
            if(node) {
                --nValid;
                s += to_string(node->val) + "@";
                q.push(node->left);
                nValid += node->left ? 1 : 0;
                q.push(node->right);
                nValid += node->right ? 1 : 0;
            }
            else {
                s += "null@";
            }
        }
        
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> inputs;
        size_t cur = 0;
        while(1) {
            size_t pos = data.find_first_of("@", cur);
            if(pos == string::npos)
                break;
            inputs.push_back(data.substr(cur, pos-cur));
            cur = pos + 1;
        }
        
        if(inputs.empty())
            return nullptr;
        
        queue<TreeNode*> q;
        TreeNode *root = new TreeNode(stoi(inputs[0]));
        q.push(root);
        int i = 1;
        while(q.size()) {
            TreeNode *node = q.front();
            q.pop();
            if(i<inputs.size() && inputs[i]!="null") {
                TreeNode *left = new TreeNode(stoi(inputs[i]));
                node->left = left;
                q.push(left);
            }
            ++i;
            if(i<inputs.size() && inputs[i]!="null") {
                TreeNode *right = new TreeNode(stoi(inputs[i]));
                node->right = right;
                q.push(right);
            }
            ++i;
        }
        
        return root;
    }
};


// Simple DFS solution using stringstream
class Codec3 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        serializeDFS(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        return deserializeDFS(iss);
    }
    
private:
    void serializeDFS(TreeNode *root, ostringstream &oss) {
        if(!root) {
            oss << "null ";
            return;
        }
        oss << root->val << " ";
        serializeDFS(root->left, oss);
        serializeDFS(root->right, oss);
    }
    
    TreeNode *deserializeDFS(istringstream &iss) {
        string val;
        iss >> val;
        if(val == "null")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserializeDFS(iss);
        root->right = deserializeDFS(iss);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


// reference from HuaHua -- using binary 1
class Codec {
public:
 
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }
 
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
private:
    enum STATUS {
        ROOT_NULL = 0x0,
        ROOT = 0x1,
        LEFT = 0x2,
        RIGHT = 0x4
    };
    
    void serialize(TreeNode* root, ostringstream& out) {
        char status = 0;
        if (root) status |= ROOT;
        if (root && root->left) status |= LEFT;
        if (root && root->right) status |= RIGHT;
        out.write(&status, sizeof(char));        
        if (!root) return;
        out.write(reinterpret_cast<char*>(&(root->val)), sizeof(root->val));
        if (root->left) serialize(root->left, out);
        if (root->right) serialize(root->right, out);
    }
    
    TreeNode* deserialize(istringstream& in) {
        char status;
        in.read(&status, sizeof(char));
        if (!status & ROOT) return nullptr;
        auto root = new TreeNode(0);
        in.read(reinterpret_cast<char*>(&root->val), sizeof(root->val));        
        root->left = (status & LEFT) ? deserialize(in) : nullptr;
        root->right = (status & RIGHT) ? deserialize(in) : nullptr;
        return root;
    }
};

// reference from HuaHua -- using binary 2
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
        return deserialize(data, pos);
    }
private:
    enum STATUS {
        ROOT_NULL = 0x0,
        ROOT = 0x1,
        LEFT = 0x2,
        RIGHT = 0x4
    };
    
    void serialize(TreeNode* root, string& s) {
        char status = ROOT_NULL;
        if (root) status |= ROOT;
        if (root && root->left) status |= LEFT;
        if (root && root->right) status |= RIGHT;
        s.push_back(status);
        if (!root) return;
        s.append(reinterpret_cast<char*>(&root->val), sizeof(root->val));
        if (root->left) serialize(root->left, s);
        if (root->right) serialize(root->right, s);
    }
    
    TreeNode* deserialize(const string& s, int& pos) {
        char status = s[pos++];
        if (!status) return nullptr;
        TreeNode* root = new TreeNode(0);
        memcpy(&root->val, s.data() + pos, sizeof(root->val));
        pos += sizeof(root->val);  
        root->left = (status & LEFT) ? deserialize(s, pos) : nullptr;
        root->right = (status & RIGHT) ? deserialize(s, pos) : nullptr;
        return root;
    }
};
