/*
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

 

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 

Constraints:

1 <= s1.length, s2.length <= 1000
s1 and s2 consist of lowercase English letters.
*/

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        // dp(m,n): lowest ASCII delete sum of s1[0:m) and s2[0:n)
        const int M = s1.size();
        const int N = s2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1,0));  // dp[0][0]=0, since there's no deletion needed for two empty strings
        for(int n=1; n<=N; ++n)  // first row
            dp[0][n] = dp[0][n-1] + s2[n-1];
        for(int m=1; m<=M; ++m)  // first col
            dp[m][0] += dp[m-1][0] + s1[m-1];
        
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(s1[m-1] == s2[n-1])
                    dp[m][n] = dp[m-1][n-1];  // no deletion needed
                else
                    dp[m][n] = min(dp[m-1][n]+s1[m-1]/*delete from s1*/, dp[m][n-1]+s2[n-1]/*delete from s2*/);
            }
        }
             
        return dp[M][N];
    }
};
