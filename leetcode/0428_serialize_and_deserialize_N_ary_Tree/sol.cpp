/*
Facebook/Google

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following 3-ary tree (format-1)

as [1 [3[5 6] 2 4]]. Note that this is just an example, you do not necessarily need to follow this format.

Or you can follow LeetCode's level order traversal serialization format, where each group of children is separated by the null value (format-2).

For example, the above tree may be serialized as [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14].

You do not necessarily need to follow the above-suggested formats, there are many more different formats that work so please be creative and come up with different approaches yourself.

Example 1:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]

Example 2:

Input: root = [1,null,3,2,4,null,5,6]
Output: [1,null,3,2,4,null,5,6]

Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
0 <= Node.val <= 10^4
The height of the n-ary tree is less than or equal to 1000
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


// BFS: node #children child-1 child-2 ......
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        ostringstream oss;
        // BFS
        queue<Node*> q;
        if(root) {
            oss << root->val;
            q.push(root);
        }
        while(!q.empty()) {
            Node *node = q.front();
            q.pop();
            oss << " " << node->children.size();
            for(Node *child : node->children) {
                oss << " " << child->val;
                q.push(child);
            }
        }
        cout << oss.str() << endl;
        return oss.str();
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if(data.empty())
            return nullptr;
        istringstream iss(data);
        int val;
        iss >> val;
        Node *root = new Node(val);
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node *node = q.front();
            q.pop();
            iss >> val;
            if(!val)  // no children
                continue;
            while(val--) {
                int val2;
                iss >> val2;
                Node *child = new Node(val2);
                node->children.push_back(child);
                q.push(child);
            }
        }

        return root;
    }
};

