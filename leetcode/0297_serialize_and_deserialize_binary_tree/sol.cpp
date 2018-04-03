/*
  Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

  Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

  For example, you may serialize the following tree

  1
  / \
  2   3
  / \
  4   5
  as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

  Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
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


// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
