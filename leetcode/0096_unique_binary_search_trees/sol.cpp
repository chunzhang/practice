/*
Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.

Example 1:
Input: n = 3
Output: 5

Example 2:
Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 19
*/

class Solution {
public:
    int numTrees(int n) {
        // dp(n): total number of unuqie BSTs
        // When we make number k as the root, left tree is dp(k-1), and right tree is dp(n-k)
        vector<int> dp(n+1, 0);  
        dp[0] = 1;  // dp(0)=1 as the base case
        for(int i=1; i<=n; ++i)
            for(int k=1; k<=i; ++k) 
                dp[i] += dp[k-1]/*left tree*/ * dp[i-k]/*right tree*/;
        return dp[n];
    }
};
