/*
Facebook

You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

 

Example 1:


Input: s = "4(2(3)(1))(6(5))"
Output: [4,2,6,3,1,5]
Example 2:

Input: s = "4(2(3)(1))(6(5)(7))"
Output: [4,2,6,3,1,5,7]
Example 3:

Input: s = "-4(2(3)(1))(6(5)(7))"
Output: [-4,2,6,3,1,5,7]
 

Constraints:

0 <= s.length <= 3 * 10^4
s consists of digits, '(', ')', and '-' only.
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


// recursively build the tree
class Solution {
public:
    TreeNode* str2tree(string s) {
        // build current node
        int i = cur;
        while(cur<s.size() && s[cur]!='(' && s[cur]!=')')
            ++cur;
        TreeNode *node = nullptr;
        if(cur>i)  // valid number
            node = new TreeNode(stoi(s.substr(i,cur-i)));

        // build left tree if exists
        if(cur<s.size() && s[cur]=='(') {
            ++cur;
            node->left = str2tree(s);
        }

        // build right tree if exists
        if(cur<s.size() && s[cur]=='(') {
            ++cur;
            node->right = str2tree(s);
        }

        // return the tree
        if(cur<s.size() && s[cur]==')')
            ++cur;
        return node;
    }

private:
    int cur = 0;
};

// ref sol: use stack to simulate recursion (in Java)
class Solution {
    public TreeNode str2tree(String s) {
        
        if (s.isEmpty()) {
            return null;
        }
        
        TreeNode root = new TreeNode();
        Stack<TreeNode> stack = new Stack<TreeNode>(); 
        stack.add(root);
        
        for (int index = 0; index < s.length();) {
            
            TreeNode node = stack.pop();
            
            // NOT_STARTED
            if (Character.isDigit(s.charAt(index)) || s.charAt(index) == '-') {
                
                Pair<Integer, Integer> numberData = this.getNumber(s, index);
                int value = numberData.getKey();
                index = numberData.getValue();
                
                node.val = value;
                
                // Next, if there is any data left, we check for the first subtree
                // which according to the problem statement will always be the left child.
                if (index < s.length() && s.charAt(index) == '(') {
                    
                    stack.add(node);

                    node.left = new TreeNode();
                    stack.add(node.left);
                }
            } else if (s.charAt(index) == '(' && node.left != null) { // LEFT_DONE
                
                stack.add(node);

                node.right = new TreeNode();
                stack.add(node.right);
            }
            
            ++index;
        }
        
        return stack.empty() ? root : stack.pop();
        
    }
    
    public Pair<Integer, Integer> getNumber(String s, int index) {
        
        boolean isNegative = false;
        
        // A negative number
        if (s.charAt(index) == '-') {
            isNegative = true;
            index++;
        }
            
        int number = 0;
        while (index < s.length() && Character.isDigit(s.charAt(index))) {
            number = number * 10 + (s.charAt(index) - '0');
            index++;
        }
        
        return new Pair<Integer, Integer>(isNegative ? -number : number, index);
    } 
}
