/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
 

Constraints:

1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.
*/

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // dp(m,n): LCS of text1[0:m) and text2[0:n)
        const int M = text1.size();
        const int N = text2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));  // first row and column is 0, which is the base case
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(text1[m-1] == text2[n-1])
                    dp[m][n] = dp[m-1][n-1] + 1;  // One may wonder what if the LCS is in dp[m-1][n]? But if that's the case, dp[m][n] is at least as good as it
                else
                    dp[m][n] = max(dp[m][n-1], dp[m-1][n]);
            }
        }
        
        return dp[M][N];
    }
};
