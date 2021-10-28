/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
*/


// DFS
// time complexity: O(N*2^(2N)), i.e., each bit can be either a left or right parenthesis
// space complexity: O(2N)
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        dfs(n, 0, 0, cur, ans);
        return ans;
    }
    
private:
    void dfs(const int n, int left, int right, string &cur, vector<string> &ans) {
        if(left==n && right==n) {
            ans.emplace_back(cur);
            return;
        }
        
        if(left<n) {  // add left parenthesis is always valid
            cur.push_back('(');
            dfs(n, left+1, right, cur, ans);
            cur.pop_back();
        }
        
        if(right<n && left>right) {  // make sure it is valid to add right parenthesis
            cur.push_back(')');
            dfs(n, left, right+1, cur, ans);
            cur.pop_back();
        }
    }
};
