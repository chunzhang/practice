/*
Facebook

Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.

The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may not pass through the root.

(Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value.)

Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: 3
Explanation: Diameter is shown in red color.

Example 2:

Input: root = [1,null,2,null,3,4,null,5,null,6]
Output: 4

Example 3:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 7
 

Constraints:

The depth of the n-ary tree is less than or equal to 1000.
The total number of nodes is between [1, 10^4].
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

// keep global answer
class Solution {
public:
    int diameter(Node* root) {
        search(root);
        return m_ans;
    }

private:
    // each call computes diameter going through root, and returns depth
    int search(Node *root) {
        if(!root)
            return 0;
        
        int max1 = 0;  // cannot initialize to INT_MIN as otherwise max1+max2 overflows
        int max2 = 0;
        for(Node *c : root->children) {
            int d = search(c);
            if(d > max1)
                swap(max1,d);
            max2 = max(max2,d);

            // alternative way to update max1 and max2
            /*
            if(d > max2) {
                int temp = max1;
                max1 = max(temp,d);
                max2 = min(temp,d);
            }
            */
        }
        m_ans = max(m_ans,max1+max2);
        return max(max1,max2) + 1;
    }

private:
    int m_ans = INT_MIN;  // global max
};
