/*
Given the root of an n-ary tree, return the postorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

 

Example 1:


Input: root = [1,null,3,2,4,null,5,6]
Output: [5,6,3,2,4,1]
Example 2:


Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
0 <= Node.val <= 10^4
The height of the n-ary tree is less than or equal to 1000.
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

// Iterative approach using stack
class Solution {
public:
    vector<int> postorder(Node* root) {
        if(!root)
            return {};
        
        deque<int> ans;  // double linked-list which supports O(1) push_front
        stack<Node*> st;
        st.push(root);
        while(!st.empty()) {
            Node *node = st.top();
            st.pop();
            ans.push_front(node->val);  // alternatively, one can also push_back to a vector, and then reverse the results to return in the end
            for(Node *child : node->children) {  // right most child to be pushed to the front of the deque first
                if(child)
                    st.push(child);
            }
        }

        return vector(ans.begin(), ans.end());
    }
};
